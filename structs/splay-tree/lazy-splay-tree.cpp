struct lazy_node {
    int val;
    int sum;
    int lazy;
    bool rev;
    int size;
    int p;
    array<int, 2> c;

    void init(int v) {
        val = v;
        sum = v;
        lazy = 0;
        rev = false;
        size = 1;
        p = 0;
        c.fill(0);
    }
};

struct lazy_splay_tree {
    int root;
    vector<lazy_node> t;

    bool is_root(int n) {
        if (n == 0) return true;
        int p = t[n].p;
        return t[p].c[0] != n and t[p].c[1] != n;
    }

    void pull(int n) {
        if (n == 0) return;
        int l = t[n].c[0], r = t[n].c[1];
        t[n].size = 1 + t[l].size + t[r].size;
        t[n].sum = t[n].val + t[l].sum + t[r].sum;
    }

    void flip(int n) {
        if (n == 0) return;
        swap(t[n].c[0], t[n].c[1]);
        t[n].rev ^= 1;
    }

    void apply(int n, int v) {
        if (n == 0) return;
        t[n].val += v;
        t[n].sum += v * t[n].size;
        t[n].lazy += v;
    }

    void push(int n) {
        if (n == 0) return;
        if (t[n].rev == 1) {
            flip(t[n].c[0]);
            flip(t[n].c[1]);
            t[n].rev = 0;
        }
        if (t[n].lazy != 0) {
            apply(t[n].c[0], t[n].lazy);
            apply(t[n].c[1], t[n].lazy);
            t[n].lazy = 0;
        }
    }

    void push_path(int n) {
        if (not is_root(n)) push_path(t[n].p);
        push(n);
    }

    void rotate(int n) {
        int p = t[n].p;
        int g = t[p].p;
        bool d = n == t[p].c[1];
        if (not is_root(p)) t[g].c[p == t[g].c[1]] = n;
        t[n].p = g;
        t[p].c[d] = t[n].c[d ^ 1];
        if (t[n].c[d ^ 1]) t[t[n].c[d ^ 1]].p = p;
        t[n].c[d ^ 1] = p;
        t[p].p = n;
        pull(p);
        pull(n);
    }

    void splay(int n, int s) {
        if (n == 0) return;
        push_path(n);
        while (t[n].p != s and not (s == 0 and is_root(n))) {
            int p = t[n].p;
            int g = t[p].p;
            if (g != s and not (s == 0 and is_root(p))) {
                if ((t[g].c[1] == p) ^ (t[p].c[1] == n)) rotate(n);
                else rotate(p);
            }
            rotate(n);
        }
        if (s == 0 and t[n].p == 0) root = n;
    }

    int kth(int k) {
        int n = root;
        while (n != 0) {
            push(n);
            int l = t[n].c[0];
            if (k < t[l].size) {
                n = l;
            } else if (k == t[l].size) {
                return n;
            } else {
                k -= t[l].size + 1;
                n = t[n].c[1];
            }
        }
        return 0;
    }

    int merge(int l, int r) {
        if (l == 0 or r == 0) return l | r;
        root = l;
        int m = kth(t[l].size - 1);
        splay(m, 0);
        t[m].c[1] = r;
        t[r].p = m;
        pull(m);
        return m;
    }

    pair<int, int> split(int n, int k) {
        if (k <= 0) return {0, n};
        if (k >= t[n].size) return {n, 0};
        root = n;
        int r = kth(k);
        splay(r, 0);
        int l = t[r].c[0];
        if (l != 0) t[l].p = 0;
        t[r].c[0] = 0;
        pull(r);
        return {l, r};
    }

    void init() {
        root = 0;
        t.clear();
        t.emplace_back();
        t[0].init(0);
        t[0].size = 0;
    }

    void insert(int i, int v) {
        int n = t.size();
        t.emplace_back();
        t[n].init(v);
        auto [l, r] = split(root, i);
        root = merge(merge(l, n), r);
    }

    void reverse(int i, int j) {
        auto [h, r] = split(root, j + 1);
        auto [l, m] = split(h, i);
        flip(m);
        root = merge(merge(l, m), r);
    }

    void update(int i, int j, int v) {
        auto [h, r] = split(root, j + 1);
        auto [l, m] = split(h, i);
        apply(m, v);
        root = merge(merge(l, m), r);
    }

    int query(int i, int j) {
        auto [h, r] = split(root, j + 1);
        auto [l, m] = split(h, i);
        int q = t[m].sum;
        root = merge(merge(l, m), r);
        return q;
    }
};
