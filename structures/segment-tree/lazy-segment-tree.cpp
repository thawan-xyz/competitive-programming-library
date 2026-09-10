struct lazy_segment_tree {
private:
    int n;
    vector<int> tree, lazy;

    void apply(int p, int x, int l) {
        tree[p] += x * l;
        lazy[p] += x;
    }

    void push(int p, int l, int r) {
        if (lazy[p] == 0) return;
        int m = (l + r) / 2;
        apply(2 * p, lazy[p], m - l + 1);
        apply(2 * p + 1, lazy[p], r - m);
        lazy[p] = 0;
    }

    void pull(int p) {
        tree[p] = tree[2 * p] + tree[2 * p + 1];
    }

    void build(int p, int l, int r, vector<int> &a) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * p, l, m, a);
        build(2 * p + 1, m + 1, r, a);
        pull(p);
    }

    void update(int p, int l, int r, int ql, int qr, int x) {
        if (qr < l or r < ql) return;
        if (ql <= l and r <= qr) {
            apply(p, x, r - l + 1);
            return;
        }
        push(p, l, r);
        int m = (l + r) / 2;
        update(2 * p, l, m, ql, qr, x);
        update(2 * p + 1, m + 1, r, ql, qr, x);
        pull(p);
    }

    int query(int p, int l, int r, int ql, int qr) {
        if (qr < l or r < ql) return 0;
        if (ql <= l and r <= qr) return tree[p];
        push(p, l, r);
        int m = (l + r) / 2;
        return query(2 * p, l, m, ql, qr) + query(2 * p + 1, m + 1, r, ql, qr);
    }

public:
    lazy_segment_tree(int n): n(n), tree(4 * n), lazy(4 * n) {}

    lazy_segment_tree(vector<int> &a): lazy_segment_tree(a.size()) {
        build(1, 0, n - 1, a);
    }

    void update(int l, int r, int x) {
        update(1, 0, n - 1, l, r, x);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
