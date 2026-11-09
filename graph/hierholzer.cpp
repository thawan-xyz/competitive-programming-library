// Eulerian Path: Hierholzer's algorithm for paths and circuits, in directed or undirected graphs
// Time: O(V + E) | Space: O(V + E)
// Note: s and t are the first and last vertices, -1 for any | returns the vertices, or empty if there is no such path
vector<int> eulerian_path(bool directed, vector<vector<pair<int, int>>> &g, int s = -1, int t = -1) {
    int n = g.size(), m = 0, k = 0;
    vector<int> d(n);
    for (int a = 0; a < n; ++a) {
        m += g[a].size();
        for (auto [b, id] : g[a]) {
            if (directed) d[a]++, d[b]--;
            else d[a] ^= 1;
        }
    }
    if (not directed) m /= 2;
    for (int a = 0; a < n; ++a) {
        if (abs(d[a]) > 1) return {};
        if (d[a] == 1) k++;
    }

    for (int a = 0; a < n; ++a) if (s == -1 and d[a] == 1 and a != t) s = a;
    if (s == -1) s = t;
    for (int a = 0; a < n; ++a) if (s == -1 and g[a].size()) s = a;
    if (s == -1) s = 0;
    if (k > 2 or (directed and k > 1) or (k > 0 and d[s] != 1)) return {};

    vector<bool> used(m + 1);
    vector<int> next(n), path, dfs = {s};
    while (dfs.size()) {
        int a = dfs.back();
        if (next[a] == g[a].size()) {
            path.push_back(a), dfs.pop_back();
        } else {
            auto [b, id] = g[a][next[a]++];
            if (not used[id]) used[id] = true, dfs.push_back(b);
        }
    }
    if (path.size() != m + 1) return {};
    reverse(path.begin(), path.end());
    if (t != -1 and path.back() != t) return {};
    return path;
}
