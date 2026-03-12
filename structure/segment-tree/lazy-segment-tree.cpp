struct lazy_segment_tree {
    int n, h;
    vector<int> tree, lazy;

    int merge(int x, int y) {
        return x + y;
    }

    void apply(int i, int x, int len) {
        tree[i] += x * len;
        if (i < n) lazy[i] += x;
    }

    void push(int k) {
        for (int s = h, len = 1 << (h - 1); s > 0; --s, len >>= 1) {
            int i = k >> s;
            if (lazy[i] != 0) {
                apply(i << 1, lazy[i], len);
                apply((i << 1) | 1, lazy[i], len);
                lazy[i] = 0;
            }
        }
    }

    void pull(int k) {
        for (int i = k >> 1, len = 2; i > 0; i >>= 1, len <<= 1) {
            tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
            if (lazy[i] != 0) tree[i] += lazy[i] * len;
        }
    }

    lazy_segment_tree(int s) {
        n = (s <= 1) ? 1 : 1 << (__lg(s - 1) + 1);
        h = __lg(n);
        tree.assign(2 * n, 0);
        lazy.assign(n, 0);
    }

    lazy_segment_tree(vector<int> &a): lazy_segment_tree(a.size()) {
        for (int i = 0; i < a.size(); ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    void update(int i, int j, int x) {
        int p = i, q = j, len = 1;
        push(p + n), push(q + n);
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1, len <<= 1) {
            if (i & 1) apply(i++, x, len);
            if (j & 1) apply(--j, x, len);
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
