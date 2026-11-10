// Kuhn's Algorithm: maximum bipartite matching
// Time: O(V E), usually much faster | Space: O(V)
// Note: g[a] has the right neighbors of left vertex a | returns match[b], the left vertex of b or -1, for b up to the largest right vertex
vector<int> kuhn(vector<vector<int>> &g) {
    int n = g.size(), m = 0, itr = 0;
    for (int a = 0; a < n; ++a) for (int b : g[a]) m = max(m, b + 1);
    vector<int> match(m, -1), vis(n, -1);
    vector<bool> used(n);

    auto dfs = [&](auto &self, int a) -> bool {
        if (vis[a] == itr) return false;
        vis[a] = itr;
        for (int b : g[a]) if (match[b] == -1) return match[b] = a, true;
        for (int b : g[a]) if (self(self, match[b])) return match[b] = a, true;
        return false;
    };

    for (bool found = true; found; ++itr) {
        found = false;
        for (int a = 0; a < n; ++a) if (not used[a] and dfs(dfs, a)) used[a] = found = true;
    }
    return match;
}
