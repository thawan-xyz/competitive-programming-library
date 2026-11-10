// Sparse Table: range queries on a static array, for an idempotent merge like min, max, gcd, and, or
// Time: O(N log N) build, O(1) query | Space: O(N log N)
// Note: query(l, r) covers [l, r] | merge(x, x) must be x, since the two halves of a query overlap
struct sparse_table {
    vector<vector<int>> table;

    static int merge(int x, int y) {
        return gcd(x, y);
    }

    sparse_table(vector<int> &a): table(1, a) {
        for (int k = 1; (1 << k) <= a.size(); ++k) {
            table.emplace_back(a.size() - (1 << k) + 1);
            for (int i = 0; i < table[k].size(); ++i) {
                table[k][i] = merge(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int l, int r) {
        int k = __lg(r - l + 1);
        return merge(table[k][l], table[k][r - (1 << k) + 1]);
    }
};
