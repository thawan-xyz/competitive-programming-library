vector<pair<int, int>> bridges(int o, vector<vector<int>> &g) {
    int n = g.size(), timer = 1;
    vector<int> in(n), low(n);
    vector<pair<int, int>> e;

    auto dfs = [&](auto &self, int a, int p) -> void {
        in[a] = low[a] = timer++;
        for (int b : g[a]) if (b != p) {
            if (in[b] != 0) {
                low[a] = min(low[a], in[b]);
            } else {
                self(self, b, a);
                low[a] = min(low[a], low[b]);
                if (in[a] < low[b]) e.emplace_back(a, b);
            }
        }
    };

    for (int i = o; i < n; ++i) if (in[i] == 0) dfs(dfs, i, i);
    return e;
}
