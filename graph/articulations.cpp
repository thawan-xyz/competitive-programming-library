vector<int> articulations(int o, vector<vector<int>> &g) {
    int n = g.size(), timer = 1;
    vector<int> in(n), low(n);
    vector<bool> art(n);

    auto dfs = [&](auto &self, int a, int p) -> void {
        in[a] = low[a] = timer++;
        int c = 0;
        for (int b : g[a]) if (b != p) {
            if (in[b] != 0) {
                low[a] = min(low[a], in[b]);
            } else {
                c++;
                self(self, b, a);
                low[a] = min(low[a], low[b]);
                if (a != p and low[b] >= in[a]) art[a] = true;
            }
        }
        if (a == p and c > 1) art[a] = true;
    };

    vector<int> points;
    for (int i = o; i < n; ++i) {
        if (in[i] == 0) dfs(dfs, i, i);
        if (art[i]) points.push_back(i);
    }
    return points;
}
