struct compact_segment_tree {
    int n;
    array<int> tree;

    compact_segment_tree(int n): n(n), tree(2 * n) {}

    void build(array<int> &a) {
        for (int i = 0; i < n; ++i) {
            tree[i + n] = a[i];
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = tree[i << 1] + tree[(i << 1) | 1];
        }
    }

    void update(int i, int x) {
        i += n, tree[i] = x;
        while (i > 1) {
            i >>= 1;
            tree[i] = tree[i << 1] + tree[(i << 1) | 1];
        }
    }

    int query(int l, int r) {
        int q = 0;
        l += n, r += n;
        while (l <= r) {
            if (l & 1) {
                q += tree[l++];
            }
            l >>= 1;
            if ((r & 1) == 0) {
                q += tree[r--];
            }
            r >>= 1;
        }
        return q;
    }
};
