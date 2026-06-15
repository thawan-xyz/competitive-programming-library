struct lazy_segment_tree {
    int n, h;
    vector<int> tree, lazy, len;

    int merge(int x, int y) {
        return x + y;
    }

    void apply(int i, int x) {
        tree[i] += x * len[i];
        if (i < n) lazy[i] += x;
    }

    void push(int k) {
        for (int s = h; s > 0; --s) {
            int i = k >> s;
            if (lazy[i] == 0) continue;
            apply(i << 1, lazy[i]);
            apply((i << 1) | 1, lazy[i]);
            lazy[i] = 0;
        }
    }

    void pull(int i) {
        while (i >>= 1) {
            tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
            if (lazy[i] != 0) tree[i] += lazy[i] * len[i];
        }
    }

    lazy_segment_tree(int s): n(1 << __lg(2 * s - 1)), h(__lg(n)), tree(2 * n), lazy(n), len(2 * n) {
        for (int i = n; i < 2 * n; ++i) len[i] = 1;
        for (int i = n - 1; i > 0; --i) len[i] = len[i << 1] + len[(i << 1) | 1];
    }

    lazy_segment_tree(vector<int> &a): lazy_segment_tree(a.size()) {
        for (int i = 0; i < a.size(); ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    void update(int i, int j, int x) {
        int p = i, q = j;
        push(p + n), push(q + n);
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) apply(i++, x);
            if (j & 1) apply(--j, x);
        }
        pull(p + n), pull(q + n);
    }

    int query(int i, int j) {
        push(i + n), push(j + n);
        int l = 0, r = 0;
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) l = merge(l, tree[i++]);
            if (j & 1) r = merge(tree[--j], r);
        }
        return merge(l, r);
    }
};
