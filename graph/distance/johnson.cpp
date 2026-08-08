vector<vector<int>> johnson(vector<vector<pair<int, int>>> &g) {
    int n = g.size();
    g.emplace_back();
    for (int i = 0; i < n; ++i) {
        g[n].emplace_back(i, 0);
    }
    vector<int> h = shortest_path_faster_algorithm(n, g);
    g.pop_back();
    if (h.empty()) return {};
    h.pop_back();
    for (int i = 0; i < n; ++i) {
        for (auto &[j, w] : g[i]) {
            w += h[i] - h[j];
        }
    }
    vector<vector<int>> d;
    for (int i = 0; i < n; ++i) {
        d.push_back(dijkstra(i, g));
        for (int j = 0; j < n; ++j) {
            if (d[i][j] != inf) d[i][j] -= h[i] - h[j];
        }
    }
    return d;
}
