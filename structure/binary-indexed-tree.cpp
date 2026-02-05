struct binary_indexed_tree_1d {
    int n;
    list<int> tree;

    static int lsb(int i) {
        return i & -i;
    }

    binary_indexed_tree_1d(int n): n(n), tree(n + 1) {}

    void build(list<int> &a) {
        for (int i = 0; i < n; ++i) modify(i, a[i]);
    }

    void modify(int i, int d) {
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

    int query(int i, int j) {
        return prefix(j) - prefix(i - 1);
    }
};

struct binary_indexed_tree_2d {
    int n, m;
    list<list<int>> tree;

    static int lsb(int i) {
        return i & -i;
    }

    binary_indexed_tree_2d(int n, int m): n(n), m(m), tree(n + 1, list<int>(m + 1)) {}

    void build(list<list<int>> &a) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                modify(i, j, a[i][j]);
            }
        }
    }

    void modify(int i, int j, int d) {
        int p = i + 1;
        while (p <= n) {
            int q = j + 1;
            while (q <= m) {
                tree[p][q] += d;
                q += lsb(q);
            }
            p += lsb(p);
        }
    }

    int prefix(int i, int j) {
        int s = 0;
        int p = i + 1;
        while (p > 0) {
            int q = j + 1;
            while (q > 0) {
                s += tree[p][q];
                q -= lsb(q);
            }
            p -= lsb(p);
        }
        return s;
    }

    int query(int i, int j, int p, int q) {
        return prefix(p, q)
             - prefix(i - 1, q)
             - prefix(p, j - 1)
             + prefix(i - 1, j - 1);
    }
};
