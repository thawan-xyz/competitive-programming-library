// Hungarian Algorithm: minimum weight bipartite matching
// Time: O(N^2 * M) | Space: O(N + M)
// Note: computes min cost assignment | negate input matrix for max
pair<int, vector<int>> hungarian(vector<vector<int>> g) {
    int n = g.size(), m = g[0].size();
    bool transposed = false;
    if (n > m) {
        transposed = true;
        vector<vector<int>> t(m, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                t[j][i] = g[i][j];
            }
        }
        swap(n, m);
        swap(g, t);
    }

    vector<int> pot_row(n + 1), pot_col(m + 1);
    vector<int> match(m + 1), prev_col(m + 1);

    for (int i = 1; i <= n; ++i) {
        match[0] = i;
        int col = 0;
        vector<int> min_cost(m + 1, inf);
        vector<bool> v(m + 1);
        do {
            v[col] = true;
            int row = match[col];
            int delta = inf;
            int next_col = 0;
            for (int j = 1; j <= m; ++j) if (not v[j]) {
                int cost = g[row - 1][j - 1] - pot_row[row] - pot_col[j];
                if (cost < min_cost[j]) {
                    min_cost[j] = cost;
                    prev_col[j] = col;
                }
                if (min_cost[j] < delta) {
                    delta = min_cost[j];
                    next_col = j;
                }
            }
            for (int j = 0; j <= m; ++j) {
                if (v[j]) {
                    pot_row[match[j]] += delta;
                    pot_col[j] -= delta;
                } else {
                    min_cost[j] -= delta;
                }
            }
            col = next_col;
        } while (match[col] != 0);
        do {
            int prev = prev_col[col];
            match[col] = match[prev];
            col = prev;
        } while (col != 0);
    }

    int cost = -pot_col[0];
    vector<int> answer(n, -1);
    for (int j = 1; j <= m; ++j) if (match[j] != 0) {
        answer[match[j] - 1] = j - 1;
    }

    if (transposed) {
        vector<int> real(m, -1);
        for (int i = 0; i < n; ++i) if (answer[i] != -1) {
            real[answer[i]] = i;
        }
        swap(answer, real);
    }
    return {cost, answer};
}
