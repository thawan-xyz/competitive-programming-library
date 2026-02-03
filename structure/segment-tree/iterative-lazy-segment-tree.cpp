struct iterative_lazy_segment_tree {
    int n, h;
    list<int> tree, lazy;

    iterative_lazy_segment_tree(int n): n(n), h(32 - __builtin_clz(n)), tree(2 * n), lazy(2 * n) {}

    int merge(int a, int b) {
        return a + b;
    }

    int compose(int c, int p) {
        if (p == 0) return c;
        return c + p;
    }

    int update(int a, int x, int l) {
        if (x == 0) return a;
        return a + x * l;
    }

    void build(list<int> &a) {
        for (int i = 0; i < n; ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    void push(int i) {
        for (int k = h; k > 0; --k) {
            int p = i >> k, l = 1 << (k - 1);
            for (int c : {p << 1, (p << 1) | 1}) {
                tree[c] = update(tree[c], lazy[p], l);
                lazy[c] = compose(lazy[c], lazy[p]);
            }
            lazy[p] = 0;
        }
    }

    void pull(int i) {
        for (int p = i >> 1, l = 2; p > 0; p >>= 1, l <<= 1) {
            tree[p] = merge(tree[p << 1], tree[(p << 1) | 1]);
            tree[p] = update(tree[p], lazy[p], l);
        }
    }

    void modify(int i, int j, int x) {
        push(i + n), push(j + n);
        for (int p = i + n, q = j + (n + 1), l = 1; p < q; p >>= 1, q >>= 1, l <<= 1) {
            if (p & 1) {
                tree[p] = update(tree[p], x, l);
                lazy[p] = compose(lazy[p], x);
                ++p;
            }
            if (q & 1) {
                --q;
                tree[q] = update(tree[q], x, l);
                lazy[q] = compose(lazy[q], x);
            }
        }
        pull(i + n), pull(j + n);
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
