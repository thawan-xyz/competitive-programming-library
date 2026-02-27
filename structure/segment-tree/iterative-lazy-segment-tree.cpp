struct iterative_lazy_segment_tree {
private:
    int n, h;
    vector<int> tree, lazy;

    int merge(int a, int b) {
        return a + b;
    }

    void update(int p, int x, int l) {
        tree[p] += x * l;
        if (p < n) {
            lazy[p] += x;
        }
    }

    void push(int i) {
        for (int k = h; k > 0; --k) {
            int p = i >> k, l = 1 << (k - 1);
            if (lazy[p] != 0) {
                update(p << 1, lazy[p], l);
                update((p << 1) | 1, lazy[p], l);
                lazy[p] = 0;
            }
        }
    }

    void pull(int i) {
        for (int p = i >> 1, l = 2; p > 0; p >>= 1, l <<= 1) {
            tree[p] = merge(tree[p << 1], tree[(p << 1) | 1]);
            if (lazy[p] != 0) {
                tree[p] += l * lazy[p];
            }
        }
    }

public:
    iterative_lazy_segment_tree(int n): n(n), h(32 - __builtin_clz(n)), tree(2 * n), lazy(n) {}

    iterative_lazy_segment_tree(vector<int> &a): n(a.size()), h(32 - __builtin_clz(n)), tree(2 * n), lazy(n) {
        for (int i = 0; i < n; ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    void modify(int i, int j, int x) {
        push(i + n), push(j + n);
        for (int p = i + n, q = j + (n + 1), l = 1; p < q; p >>= 1, q >>= 1, l <<= 1) {
            if (p & 1) update(p++, x, l);
            if (q & 1) update(--q, x, l);
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
