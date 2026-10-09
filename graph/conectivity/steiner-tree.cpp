vector<vector<int>> steiner_tree(int n, int k, const vector<vector<int>> &dist) {
    vector<vector<int>> steiner(1 << k, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) steiner[0][i] = 0;
    for (int i = 0; i < k; ++i) steiner[1 << i][i] = 0;
    for (int mask = 1; mask < (1 << k); ++mask) {
        for (int sub = mask; sub > 0; sub = mask & (sub - 1)) {
            for (int i = 0; i < n; ++i) {
                steiner[mask][i] = min(steiner[mask][i], steiner[sub][i] + steiner[mask ^ sub][i]);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                steiner[mask][j] = min(steiner[mask][j], steiner[mask][i] + dist[i][j]);
            }
        }
    }
    return steiner;
}
