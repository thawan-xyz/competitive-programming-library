vector<pair<int, int>> bridges(int r, vector<vector<int>> &g) {
    int n = g.size(), timer = 1;
    vector<int> in(n), low(n);
    vector<pair<int, int>> edges;

    function<void(int, int)> dfs = [&](int a, int p) -> void {
        in[a] = low[a] = timer++;
        for (int b : g[a]) if (b != p) {
            if (in[b] != 0) {
                low[a] = min(low[a], in[b]);
            } else {
                dfs(b, a);
                low[a] = min(low[a], low[b]);
                if (in[a] < low[b]) edges.push_back({a, b});
            }
        }
    };

    for (int i = r; i < n; ++i) if (in[i] == 0) dfs(i, i);
    return edges;
}
