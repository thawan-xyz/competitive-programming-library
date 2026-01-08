struct binary_indexed_tree_2d {
    int n, m;
    array<array<int>> tree;

    static int lsb(int i) {
        return i & -i;
    }

    binary_indexed_tree_2d(int n, int m): n(n), m(m), tree(n + 1, array<int>(m + 1)) {}

    void build(array<array<int>> &a) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                update(i, j, a[i][j]);
            }
        }
    }

    void update(int i_, int j_, int d) {
        int i = i_ + 1;
        while (i <= n) {
            int j = j_ + 1;
            while (j <= m) {
                tree[i][j] += d;
                j += lsb(j);
            }
            i += lsb(i);
        }
    }

    int prefix(int i_, int j_) {
        int s = 0;
        int i = i_ + 1;
        while (i > 0) {
            int j = j_ + 1;
            while (j > 0) {
                s += tree[i][j];
                j -= lsb(j);
            }
            i -= lsb(i);
        }
        return s;
    }

    int query(int i1, int j1, int i2, int j2) {
        return prefix(i2, j2)
             - prefix(i1 - 1, j2)
             - prefix(i2, j1 - 1)
             + prefix(i1 - 1, j1 - 1);
    }
};
