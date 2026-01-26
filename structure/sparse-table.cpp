struct sparse_table {
    int n;
    list<list<int>> table;

    static int log2(int x) {
        return __lg(x);
    }

    static int pow2(int x) {
        return 1 << x;
    }

    sparse_table(int n): n(n), table(n, list<int>(log2(n) + 1)) {}

    int merge(int x, int y) {
        return gcd(x, y);
    }

    void build(list<int> &a) {
        for (int i = 0; i < n; ++i) {
            table[i][0] = a[i];
        }
        for (int k = 1; k <= log2(n); ++k) {
            for (int i = 0; i + (pow2(k) - 1) < n; ++i) {
                table[i][k] = merge(table[i][k - 1], table[i + pow2(k - 1)][k - 1]);
            }
        }
    }

    int query(int l, int r) {
        int k = log2(r - l + 1);
        return merge(table[l][k], table[r - (pow2(k) - 1)][k]);
    }
};
