// Undirected Eulerian Path: Hierholzer's algorithm for paths and circuits
// Time: O(V + E) | Space: O(V + E)
// Note: returns sequence of vertices or empty if impossible | s must be a valid start node
vector<int> undirected_eulerian_path(int s, vector<vector<pair<int, int>>> &g, int e) {
    int n = g.size();
    int odd = 0;
    for (int i = 0; i < n; ++i) {
        if (g[i].size() & 1) odd++;
    }
    if (odd != 0 and odd != 2) return {};
    if (odd == 2 and (g[s].size() & 1) == 0) return {};
    vector<bool> used(e + 1);
    vector<int> next(n), path;
    auto hierholzer = [&](auto &self, int a) -> void {
        while (next[a] < g[a].size()) {
            auto [b, id] = g[a][next[a]];
            next[a]++;
            if (not used[id]) {
                used[id] = true;
                self(self, b);
            }
        }
        path.push_back(a);
    };
    hierholzer(hierholzer, s);
    if (path.size() != e + 1) return {};
    reverse(path.begin(), path.end());
    return path;
}

// Directed Eulerian Path: Hierholzer's algorithm for paths and circuits
// Time: O(V + E) | Space: O(V + E)
// Note: returns sequence of vertices or empty if impossible | s must be a valid start node
vector<int> directed_eulerian_path(int s, vector<vector<int>> &g, int e) {
    int n = g.size();
    vector<int> in(n), out(n);
    for (int a = 0; a < n; ++a) {
        out[a] = g[a].size();
        for (int b : g[a]) {
            in[b]++;
        }
    }
    int start = 0, end = 0;
    for (int i = 0; i < n; ++i) {
        if (out[i] - in[i] == +1) start++;
        else if (out[i] - in[i] == -1) end++;
        else if (out[i] - in[i] != 0) return {};
    }
    if (not ((start == 0 and end == 0) or (start == 1 and end == 1))) return {};
    if (start == 1 and out[s] - in[s] != +1) return {};
    vector<int> next(n), path;
    auto hierholzer = [&](auto &self, int a) -> void {
        while (next[a] < g[a].size()) {
            int b = g[a][next[a]];
            next[a]++;
            self(self, b);
        }
        path.push_back(a);
    };
    hierholzer(hierholzer, s);
    if (path.size() != e + 1) return {};
    reverse(path.begin(), path.end());
    return path;
}
