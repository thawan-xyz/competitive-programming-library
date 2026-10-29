// Treap: dynamic array with insert, erase, set, move, reverse, range update and range query
// Time: O(log N) expected per operation | Space: O(N) | needs rng (mt19937) | edit node, pull and apply
// Note: 0-based positions | less(x) = count < x, only if the array is kept sorted with insert(less(x), x)
struct treap {
    struct node {
        int val = 0, pri = rng();
        int sum = 0, lazy = 0;
        bool rev = false;
        int size = 0, l = 0, r = 0;
    };

    void pull(int n) {
        node &a = tree[n], &l = tree[a.l], &r = tree[a.r];
        a.size = l.size + 1 + r.size;
        a.sum = l.sum + a.val + r.sum;
    }

    void apply(int n, int x) {
        if (n == 0) return;
        tree[n].val += x;
        tree[n].sum += x * tree[n].size;
        tree[n].lazy += x;
    }

    int root = 0;
    vector<node> tree = {node()};

    treap(const vector<int> &a = {}) {
        for (int x : a) root = merge(root, make(x));
    }

    int make(int x) {
        tree.push_back({x});
        pull(tree.size() - 1);
        return tree.size() - 1;
    }

    void flip(int n) {
        if (n == 0) return;
        swap(tree[n].l, tree[n].r);
        tree[n].rev ^= 1;
    }

    void push(int n) {
        if (tree[n].rev) flip(tree[n].l), flip(tree[n].r), tree[n].rev = false;
        if (tree[n].lazy != tree[0].lazy) {
            apply(tree[n].l, tree[n].lazy), apply(tree[n].r, tree[n].lazy);
            tree[n].lazy = tree[0].lazy;
        }
    }

    array<int, 2> split(int n, int k) {
        if (n == 0) return {0, 0};
        push(n);
        int s = tree[tree[n].l].size;
        if (k <= s) {
            auto [a, b] = split(tree[n].l, k);
            tree[n].l = b;
            pull(n);
            return {a, n};
        }
        auto [a, b] = split(tree[n].r, k - s - 1);
        tree[n].r = a;
        pull(n);
        return {n, b};
    }

    int merge(int a, int b) {
        if (a == 0 or b == 0) return a | b;
        if (tree[a].pri > tree[b].pri) {
            push(a);
            tree[a].r = merge(tree[a].r, b);
            pull(a);
            return a;
        }
        push(b);
        tree[b].l = merge(a, tree[b].l);
        pull(b);
        return b;
    }

    array<int, 3> split3(int l, int r) {
        auto [a, b] = split(root, l);
        auto [m, c] = split(b, r - l + 1);
        return {a, m, c};
    }

    void merge3(int a, int m, int c) {
        root = merge(merge(a, m), c);
    }

    void insert(int i, int x) {
        auto [a, b] = split(root, i);
        root = merge(merge(a, make(x)), b);
    }

    void erase(int l, int r) {
        auto [a, m, c] = split3(l, r);
        root = merge(a, c);
    }

    void set(int i, int x) {
        auto [a, m, c] = split3(i, i);
        tree[m].val = x;
        pull(m);
        merge3(a, m, c);
    }

    void move(int l, int r, int k) {
        auto [a, m, c] = split3(l, r);
        auto [d, e] = split(merge(a, c), k);
        root = merge(merge(d, m), e);
    }

    void reverse(int l, int r) {
        auto [a, m, c] = split3(l, r);
        flip(m);
        merge3(a, m, c);
    }

    void update(int l, int r, int x) {
        auto [a, m, c] = split3(l, r);
        apply(m, x);
        merge3(a, m, c);
    }

    node query(int l, int r) {
        auto [a, m, c] = split3(l, r);
        node q = tree[m];
        merge3(a, m, c);
        return q;
    }

    int less(int x) {
        int i = 0, n = root;
        while (n != 0) {
            push(n);
            if (tree[n].val < x) i += tree[tree[n].l].size + 1, n = tree[n].r;
            else n = tree[n].l;
        }
        return i;
    }
};
