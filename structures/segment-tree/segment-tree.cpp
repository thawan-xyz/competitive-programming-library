struct segment_tree {
    int n;
    vector<int> tree;

    int merge(int x, int y) {
        return x + y;
    }

    segment_tree(int s): n(__bit_ceil(s)), tree(2 * n) {}

    segment_tree(vector<int> &a): segment_tree(a.size()) {
        for (int i = 0; i < a.size(); ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    void update(int i, int x) {
        i += n;
        tree[i] = x;
        while (i >>= 1) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    int query(int i, int j) {
        int l = 0, r = 0;
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) l = merge(l, tree[i++]);
            if (j & 1) r = merge(tree[--j], r);
        }
        return merge(l, r);
    }
};

struct segment_tree {
private:
    int n;
    vector<int> tree;

    int merge(int x, int y) {
        return x + y;
    }

    void build(int p, int l, int r, vector<int> &a) {
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * p, l, m, a);
        build((2 * p) + 1, m + 1, r, a);
        tree[p] = merge(tree[2 * p], tree[(2 * p) + 1]);
    }

    void update(int p, int l, int r, int i, int x) {
        if (i < l or r < i) return;
        if (l == r) {
            tree[p] = x;
            return;
        }
        int m = (l + r) / 2;
        update(2 * p, l, m, i, x);
        update((2 * p) + 1, m + 1, r, i, x);
        tree[p] = merge(tree[2 * p], tree[(2 * p) + 1]);
    }

    int query(int p, int l, int r, int ql, int qr) {
        if (qr < l or r < ql) return 0;
        if (ql <= l and r <= qr) return tree[p];
        int m = (l + r) / 2;
        return merge(query(2 * p, l, m, ql, qr), query((2 * p) + 1, m + 1, r, ql, qr));
    }

public:
    segment_tree(int n): n(n), tree(4 * n) {}

    segment_tree(vector<int> &a): n(a.size()), tree(4 * n) {
        build(1, 0, n - 1, a);
    }

    void update(int i, int x) {
        update(1, 0, n - 1, i, x);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};
