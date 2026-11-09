vector<int> articulations(vector<vector<int>> &g) {
    int n = g.size(), t = 0;
    vector<int> tin(n, -1), low(n), points;
    vector<bool> art(n);

    auto dfs = [&](auto &self, int a, int p) -> void {
        tin[a] = low[a] = t++;
        int c = 0;
        for (int b : g[a]) if (b != p) {
            if (tin[b] != -1) {
                low[a] = min(low[a], tin[b]);
            } else {
                c++;
                self(self, b, a);
                low[a] = min(low[a], low[b]);
                if (p != -1 and low[b] >= tin[a]) art[a] = true;
            }
        }
        if (p == -1 and c > 1) art[a] = true;
    };

    for (int i = 0; i < n; ++i) {
        if (tin[i] == -1) dfs(dfs, i, -1);
        if (art[i]) points.push_back(i);
    }
    return points;
}
