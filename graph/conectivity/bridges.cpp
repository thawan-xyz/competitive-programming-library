vector<pair<int, int>> bridges(vector<vector<int>> &g) {
    int n = g.size(), t = 0;
    vector<int> tin(n, -1), low(n);
    vector<pair<int, int>> e;

    auto dfs = [&](auto &self, int a, int p) -> void {
        tin[a] = low[a] = t++;
        bool parent = true;
        for (int b : g[a]) {
            if (b == p and parent) {
                parent = false;
            } else if (tin[b] != -1) {
                low[a] = min(low[a], tin[b]);
            } else {
                self(self, b, a);
                low[a] = min(low[a], low[b]);
                if (tin[a] < low[b]) e.emplace_back(a, b);
            }
        }
    };

    for (int i = 0; i < n; ++i) if (tin[i] == -1) dfs(dfs, i, -1);
    return e;
}
