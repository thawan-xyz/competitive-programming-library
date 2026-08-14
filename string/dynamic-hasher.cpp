struct dynamic_hasher {
    int n;
    vector<hashes> tree;

    dynamic_hasher(const string &s): n(s.length()), tree(2 * n) {
        for (int i = 0; i < n; ++i) tree[n + i] = hashes(s[i]);
        for (int i = n - 1; i > 0; --i) tree[i] = combine(tree[i << 1], tree[(i << 1) | 1]);
    }

    void update(int i, char c) {
        tree[i += n] = hashes(c);
        for (i >>= 1; i > 0; i >>= 1) tree[i] = combine(tree[i << 1], tree[(i << 1) | 1]);
    }

    hashes query(int i, int j) {
        hashes l, r;
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) l = combine(l, tree[i++]);
            if (j & 1) r = combine(tree[--j], r);
        }
        return combine(l, r);
    }
};
