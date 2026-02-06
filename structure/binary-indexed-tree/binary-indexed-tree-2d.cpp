struct binary_indexed_tree_2d {
    int n, m;
    list<binary_indexed_tree> tree;

    static int lsb(int i) {
        return i & -i;
    }

    binary_indexed_tree_2d(int n = 0, int m = 0): n(n), m(m), tree(n + 1, binary_indexed_tree(m)) {}

    void build(list<list<int>> &a) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                modify(i, j, a[i][j]);
            }
        }
    }

    int prefix(int i, int j) {
        int s = 0;
        i += 1;
        while (i > 0) {
            s += tree[i].prefix(j);
            i -= lsb(i);
        }
        return s;
    }

    int query(int i, int j, int p, int q) {
        return prefix(p, q)
             - prefix(i - 1, q)
             - prefix(p, j - 1)
             + prefix(i - 1, j - 1);
    }

    void modify(int i, int j, int d) {
        i += 1;
        while (i <= n) {
            tree[i].modify(j, d);
            i += lsb(i);
        }
    }
};
