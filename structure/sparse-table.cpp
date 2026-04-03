struct sparse_table {
    int n, l;
    vector<vector<int>> table;

    int merge(int x, int y) {
        return gcd(x, y);
    }

    sparse_table(vector<int> &a): n(a.size()), l(__lg(n)), table(l + 1, vector<int>(n)) {
        for (int i = 0; i < n; ++i) table[0][i] = a[i];
        for (int k = 1; k <= l; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                table[k][i] = merge(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int i, int j) {
        int k = __lg(j - i + 1), p = 1 << k;
        return merge(table[k][i], table[k][j - p + 1]);
    }
};
