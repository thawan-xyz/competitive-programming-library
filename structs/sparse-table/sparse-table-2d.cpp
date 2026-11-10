// Sparse Table 2D: rectangle queries on a static matrix, for an idempotent merge like min, max, gcd, and, or
// Time: O(N M log N log M) build, O(1) query | Space: O(N M log N log M)
// Note: requires sparse_table, whose merge is used | query(r1, c1, r2, c2) covers rows [r1, r2] and columns [c1, c2]
struct sparse_table_2d {
    vector<vector<sparse_table>> table;

    sparse_table_2d(vector<vector<int>> &a): table(1) {
        for (auto &row : a) table[0].emplace_back(row);
        for (int k = 1; (1 << k) <= a.size(); ++k) {
            table.emplace_back();
            for (int i = 0; i + (1 << k) <= a.size(); ++i) {
                vector<int> row = table[k - 1][i].table[0];
                auto &other = table[k - 1][i + (1 << (k - 1))].table[0];
                for (int j = 0; j < row.size(); ++j) row[j] = sparse_table::merge(row[j], other[j]);
                table[k].emplace_back(row);
            }
        }
    }

    int query(int r1, int c1, int r2, int c2) {
        int k = __lg(r2 - r1 + 1);
        return sparse_table::merge(table[k][r1].query(c1, c2), table[k][r2 - (1 << k) + 1].query(c1, c2));
    }
};
