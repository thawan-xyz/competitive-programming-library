struct compact_segment_tree {
    int n;
    array<int> t;

    compact_segment_tree(int n): n(n), t(2 * n) {}

    void build(array<int> &a) {
        for (int i = 0; i < n; ++i) t[i + n] = a[i];

        for (int i = n - 1; i > 0; --i) t[i] = t[i << 1] + t[(i << 1) | 1];
    }

    void update(int i, int v) {
        i += n, t[i] = v;
        while (i > 1) {
            i >>= 1;
            t[i] = t[i << 1] + t[(i << 1) | 1];
        }
    }

    int query(int l, int r) {
        int a = 0;
        l += n, r += n;
        while (l <= r) {
            if (l & 1) a += t[l++];
            if (!(r & 1)) a += t[r--];
            l >>= 1, r >>= 1;
        }
        return a;
    }
};
