struct sparse_table_2d {
    int n, m, l;
    vector<vector<sparse_table>> table;

    sparse_table_2d(vector<vector<int>> &a): n(a.size()), m(a[0].size()), l(__lg(n)), table(l + 1) {
        for (int i = 0; i < n; ++i) {
            table[0].push_back(sparse_table(a[i]));
        }
        for (int k = 1; k <= l; ++k) {
            for (int i = 0; i + (1 << k) <= n; ++i) {
                vector<int> h(m);
                for (int j = 0; j < m; ++j) {
                    int x = table[k - 1][i].table[0][j];
                    int y = table[k - 1][i + (1 << (k - 1))].table[0][j];
                    h[j] = sparse_table::merge(x, y);
                }
                table[k].push_back(sparse_table(h));
            }
        }
    }

    int query(int i1, int j1, int i2, int j2) {
        int k = __lg(i2 - i1 + 1);
        int x = table[k][i1].query(j1, j2);
        int y = table[k][i2 - (1 << k) + 1].query(j1, j2);
        return sparse_table::merge(x, y);
    }
};
