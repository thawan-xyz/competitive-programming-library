struct segment_tree_2d {
    int n, m;
    vector<segment_tree> tree;

    segment_tree_2d(int n, int m): n(n), m(m), tree(2 * n, segment_tree(m)) {}

    segment_tree_2d(vector<vector<int>> &a): segment_tree_2d(a.size(), a[0].size()) {
        for (int i = 0; i < n; ++i) tree[n + i] = segment_tree(a[i]);
        for (int i = n - 1; i > 0; --i) {
            for (int j = 1; j < 2 * m; ++j) {
                tree[i].tree[j] = segment_tree::merge(tree[i << 1].tree[j], tree[(i << 1) | 1].tree[j]);
            }
        }
    }

    void update(int i, int j, int x) {
        tree[i += n].update(j, x);
        while (i >>= 1) tree[i].update(j, segment_tree::merge(tree[i << 1].tree[j + m], tree[(i << 1) | 1].tree[j + m]));
    }

    int query(int i1, int j1, int i2, int j2) {
        int l = 0, r = 0;
        for (i1 += n, i2 += n + 1; i1 < i2; i1 >>= 1, i2 >>= 1) {
            if (i1 & 1) l = segment_tree::merge(l, tree[i1++].query(j1, j2));
            if (i2 & 1) r = segment_tree::merge(tree[--i2].query(j1, j2), r);
        }
        return segment_tree::merge(l, r);
    }
};
