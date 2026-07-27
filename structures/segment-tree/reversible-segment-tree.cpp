struct reversible_segment_tree {
    int n;
    bool v;
    vector<int> tree;

    int merge(int x, int y) {
        return x + y;
    }

    int combine(int x, int y) {
        if (v) return merge(y, x);
        return merge(x, y);
    }

    reversible_segment_tree(int s, bool v): n(__bit_ceil(s)), v(v), tree(2 * n) {}

    reversible_segment_tree(vector<int> &a, bool v): reversible_segment_tree(a.size(), v) {
        for (int i = 0; i < a.size(); ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = combine(tree[i << 1], tree[(i << 1) | 1]);
    }

    void update(int i, int x) {
        tree[i += n] = x;
        while (i >>= 1) tree[i] = combine(tree[i << 1], tree[(i << 1) | 1]);
    }

    int query(int i, int j) {
        int l = 0, r = 0;
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) l = combine(l, tree[i++]);
            if (j & 1) r = combine(tree[--j], r);
        }
        return combine(l, r);
    }
};
