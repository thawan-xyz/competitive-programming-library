// Implicit Treap: dynamic array with range updates and queries
// Time: operations O(log N) average | Space: O(N)
// Note: supports range modifications | uses lazy propagation and implicit indices
struct treap {
    struct node {
        int x, p, l = 0, r = 0;
        int sum, size = 1, lazy = 0, rev = 0;

        node(int x, int p = rng()): x(x), p(p), sum(x) {}
    };

    int root = 0;
    vector<node> t;

    treap(int n = 0) {
        t.reserve(n + 1);
        t.push_back(node(0));
        t[0].size = 0;
    }

    void apply(int i, int x) {
        if (i == 0) return;
        t[i].x += x;
        t[i].sum += x * t[i].size;
        t[i].lazy += x;
    }

    void flip(int i) {
        if (i == 0) return;
        swap(t[i].l, t[i].r);
        t[i].rev ^= 1;
    }

    void push(int i) {
        if (i == 0) return;
        if (t[i].rev != 0) {
            flip(t[i].l);
            flip(t[i].r);
            t[i].rev = 0;
        }
        if (t[i].lazy != 0) {
            apply(t[i].l, t[i].lazy);
            apply(t[i].r, t[i].lazy);
            t[i].lazy = 0;
        }
    }

    void pull(int i) {
        if (i == 0) return;
        t[i].size = t[t[i].l].size + 1 + t[t[i].r].size;
        t[i].sum = t[t[i].l].sum + t[i].x + t[t[i].r].sum;
    }

    pair<int, int> split(int i, int k) {
        if (i == 0) return {0, 0};
        push(i);
        int s = t[t[i].l].size;
        if (s >= k) {
            auto [l, r] = split(t[i].l, k);
            t[i].l = r;
            pull(i);
            return {l, i};
        } else {
            auto [l, r] = split(t[i].r, k - s - 1);
            t[i].r = l;
            pull(i);
            return {i, r};
        }
    }

    int merge(int l, int r) {
        if (l == 0 or r == 0) return l | r;
        if (t[l].p > t[r].p) {
            push(l);
            t[l].r = merge(t[l].r, r);
            pull(l);
            return l;
        } else {
            push(r);
            t[r].l = merge(l, t[r].l);
            pull(r);
            return r;
        }
    }

    void insert(int k, int x) {
        auto [l, r] = split(root, k);
        int i = t.size();
        t.push_back(node(x));
        root = merge(merge(l, i), r);
    }

    void erase(int k) {
        auto [l, m] = split(root, k);
        auto [_, r] = split(m, 1);
        root = merge(l, r);
    }

    void move(int i, int j, int k) {
        auto [h, q] = split(root, j + 1);
        auto [p, m] = split(h, i);
        auto [l, r] = split(merge(p, q), k);
        root = merge(merge(l, m), r);
    }

    void reverse(int i, int j) {
        auto [h, r] = split(root, j + 1);
        auto [l, m] = split(h, i);
        flip(m);
        root = merge(merge(l, m), r);
    }

    void update(int i, int j, int x) {
        auto [h, r] = split(root, j + 1);
        auto [l, m] = split(h, i);
        apply(m, x);
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
