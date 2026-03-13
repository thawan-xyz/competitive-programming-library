struct sparse_table {
    int n;
    vector<vector<int>> table;

    int merge(int x, int y) {
        return gcd(x, y);
    }

    sparse_table(vector<int> &a): n(a.size()), table(__lg(n) + 1, vector<int>(n)) {
        for (int i = 0; i < n; ++i) table[0][i] = a[i];
        for (int i = 1; i <= __lg(n); ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                table[i][j] = merge(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int i, int j) {
        int k = __lg(j - i + 1);
        return merge(table[k][i], table[k][j - (1 << k) + 1]);
    }
};
