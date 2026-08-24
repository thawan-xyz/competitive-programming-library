struct segment_tree {
    int n;
    vector<int> tree;

    int merge(int x, int y) {
        return x + y;
    }

    segment_tree(int s): n(__bit_ceil(s)), tree(2 * n) {}

    segment_tree(vector<int> &a): segment_tree(a.size()) {
        for (int i = 0; i < a.size(); ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    void update(int i, int x) {
        i += n;
        tree[i] = x;
        while (i /= 2) tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
    }

    int query(int i, int j) {
        int l = 0, r = 0;
        for (i += n, j += n + 1; i < j; i /= 2, j /= 2) {
            if (i & 1) l = merge(l, tree[i++]);
            if (j & 1) r = merge(tree[--j], r);
        }
        return merge(l, r);
    }
};
