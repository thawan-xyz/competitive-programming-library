struct segment_tree {
    int n;
    vector<int> tree;

    int merge(int x, int y) {
        return x + y;
    }

    segment_tree(int n): n(n), tree(2 * n) {}

    segment_tree(vector<int> &a): segment_tree(a.size()) {
        for (int i = 0; i < n; ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    void update(int i, int x) {
        tree[i += n] = x;
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
