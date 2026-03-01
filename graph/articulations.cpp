vector<int> articulations(int r, vector<vector<int>> &g) {
    int n = g.size(), timer = 1;
    vector<int> in(n), low(n);
    vector<bool> articulation(n);

    function<void(int, int)> dfs = [&](int a, int p) -> void {
        in[a] = low[a] = timer++;
        int children = 0;
        for (int b : g[a]) if (b != p) {
            if (in[b] != 0) {
                low[a] = min(low[a], in[b]);
            } else {
                children++;
                dfs(b, a);
                low[a] = min(low[a], low[b]);
                if (low[b] >= in[a]) articulation[a] = true;
            }
        }
        if (p == 0) articulation[a] = children > 1;
    };
    for (int i = r; i < n; ++i) if (in[i] == 0) dfs(i, i);

    vector<int> points;
    for (int i = r; i < n; ++i) if (articulation[i]) points.push_back(i);
    return points;
}
