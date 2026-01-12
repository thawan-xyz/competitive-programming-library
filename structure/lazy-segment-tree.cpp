struct lazy_segment_tree {
    int n, h;
    array<int> tree, lazy;

    lazy_segment_tree(int n): n(n), h(32 - __builtin_clz(n)), tree(2 * n), lazy(2 * n) {}

    int combine(int a, int b) {
        return a + b;
    }

    int apply(int a, int x, int l) {
        return a + x * l;
    }

    void build(array<int> &a) {
        for (int i = 0; i < n; ++i) {
            tree[n + i] = a[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = combine(tree[i << 1], tree[(i << 1) | 1]);
        }
    }

    void push(int i) {
        for (int k = h; k > 0; --k) {
            int p = i >> k;
            int l = 1 << (k - 1);
            if (lazy[p] != 0) {
                lazy[p << 1] = combine(lazy[p << 1], lazy[p]);
                tree[p << 1] = apply(tree[p << 1], lazy[p], l);
                lazy[(p << 1) | 1] = combine(lazy[(p << 1) | 1], lazy[p]);
                tree[(p << 1) | 1] = apply(tree[(p << 1) | 1], lazy[p], l);
            }
            lazy[p] = 0;
        }
    }

    void pull(int i) {
        for (int p = i >> 1, l = 2; p > 0; p >>= 1, l <<= 1) {
            tree[p] = combine(tree[p << 1], tree[(p << 1) | 1]);
            tree[p] = apply(tree[p], lazy[p], l);
        }
    }

    void update(int i, int j, int x) {
        for (int p = i + n, q = j + (n + 1), l = 1; p < q; p >>= 1, q >>= 1, l <<= 1) {
            if (p & 1) {
                lazy[p] = combine(lazy[p], x);
                tree[p] = apply(tree[p], x, l);
                ++p;
            }
            if (q & 1) {
                --q;
                lazy[q] = combine(lazy[q], x);
                tree[q] = apply(tree[q], x, l);
            }
        }
        pull(i + n);
        pull(j + n);
    }

    int query(int i, int j) {
        push(i + n);
        push(j + n);
        int l = 0;
        int r = 0;
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) {
                l = combine(l, tree[i]);
                ++i;
            }
            if (j & 1) {
                --j;
                r = combine(tree[j], r);
            }
        }
        return combine(l, r);
    }
};
