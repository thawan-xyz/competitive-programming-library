struct iterative_segment_tree {
    int n;
    list<int> tree;

    iterative_segment_tree(int n): n(n), tree(2 * n) {}

    int merge(int a, int b) {
        return a + b;
    }

    void build(list<int> &a) {
        for (int i = 0; i < n; ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    void modify(int i, int x) {
        i += n;
        tree[i] = x;
        for (i >>= 1; i > 0; i >>= 1) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
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
