struct lazy_segment_tree {
private:
    int n;
    vector<int> tree, lazy;

    void build(vector<int> &a, int p, int l, int r) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, 2 * p, l, m);
        build(a, (2 * p) + 1, m + 1, r);
        tree[p] = tree[2 * p] + tree[(2 * p) + 1];
    }

    void apply(int p, int x, int len) {
        tree[p] += x * len;
        lazy[p] += x;
    }

    void push(int p, int l, int r) {
        if (lazy[p] == 0) return;
        int m = (l + r) / 2;
        apply(2 * p, lazy[p], m - l + 1);
        apply((2 * p) + 1, lazy[p], r - m);
        lazy[p] = 0;
    }

    void update(int ql, int qr, int x, int p, int l, int r) {
        if (qr < l or r < ql) return;
        if (ql <= l and r <= qr) {
            apply(p, x, r - l + 1);
            return;
        }
        push(p, l, r);
        int m = (l + r) / 2;
        update(ql, qr, x, 2 * p, l, m);
        update(ql, qr, x, (2 * p) + 1, m + 1, r);
        tree[p] = tree[2 * p] + tree[(2 * p) + 1];
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (qr < l or r < ql) return 0;
        if (ql <= l and r <= qr) return tree[p];
        push(p, l, r);
        int m = (l + r) / 2;
        return query(ql, qr, 2 * p, l, m) + query(ql, qr, (2 * p) + 1, m + 1, r);
    }

public:
    lazy_segment_tree(int n): n(n), tree(4 * n), lazy(4 * n) {}

    lazy_segment_tree(vector<int> &a): n(a.size()), tree(4 * n), lazy(4 * n) {
        build(a, 1, 0, n - 1);
    }

    void update(int l, int r, int x) {
        update(l, r, x, 1, 0, n - 1);
    }

    int query(int l, int r) {
        return query(l, r, 1, 0, n - 1);
    }
};
