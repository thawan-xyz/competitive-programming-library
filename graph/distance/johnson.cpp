// Johnson: all pairs shortest paths with negative edges, using potentials from SPFA and Dijkstra from each vertex
// Time: O(n m log n) | Space: O(n^2 + m)
// Note: requires spfa (bellman-ford) and dijkstra | returns d[i][j] (inf if unreachable), or empty on a negative cycle
vector<vector<int>> johnson(vector<vector<pair<int, int>>> g) {
    int n = g.size();
    g.emplace_back();
    for (int i = 0; i < n; ++i) g[n].emplace_back(i, 0);
    vector<int> h = spfa(n, g);
    if (h.empty()) return {};
    g.pop_back();
    for (int i = 0; i < n; ++i) {
        for (auto &[j, w] : g[i]) w += h[i] - h[j];
    }
    vector<vector<int>> d(n);
    for (int i = 0; i < n; ++i) {
        d[i] = dijkstra(i, g);
        for (int j = 0; j < n; ++j) if (d[i][j] != inf) d[i][j] -= h[i] - h[j];
    }
    return d;
}
