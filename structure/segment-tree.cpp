struct segment_tree {
    int n;
    array<int> tree;

    segment_tree(int n): n(n), tree(2 * n) {}

    int combine(int a, int b) {
        return a + b;
    }

    void build(array<int> &a) {
        for (int i = 0; i < n; ++i) {
            tree[n + i] = a[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = combine(tree[i << 1], tree[(i << 1) | 1]);
        }
    }

    void update(int i, int x) {
        i += n;
        tree[i] = x;
        for (i >>= 1; i > 0; i >>= 1) {
            tree[i] = combine(tree[i << 1], tree[(i << 1) | 1]);
        }
    }

    int query(int i, int j) {
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
