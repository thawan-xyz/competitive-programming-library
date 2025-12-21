struct binary_indexed_tree {
    int n;
    array<int> tree;

    static int lsb(int i) {
        return i & -i;
    }

    binary_indexed_tree(int n): n(n), tree(n + 1) {}

    void build(array<int> &base) {
        for (int i = 0; i < n; ++i) update(i, base[i]);
    }

    void update(int i, int d) {
        i += 1;
        while (i <= n) {
            tree[i] += d;
            i += lsb(i);
        }
    }

    int prefix(int i) {
        int s = 0;
        i += 1;
        while (i > 0) {
            s += tree[i];
            i -= lsb(i);
        }
        return s;
    }

    int kth(int k) {
        int i = 0;
        for (int j = 1 << (31 - __builtin_clz(n)); j > 0; j >>= 1) {
            if (i + j <= n and tree[i + j] < k) {
                k -= tree[i + j];
                i += j;
            }
        }
        return i;
    }
};
