// Kuhn's Algorithm: maximum matching in a bipartite graph
// Time: O(V E), usually much faster | Space: O(V)
// Note: returns match[a], the vertex matched with a or -1
vector<int> kuhn(vector<vector<int>> &g) {
    int n = g.size(), itr = 0;
    vector<int> match(n, -1), vis(n, -1), side(n, -1);
    for (int s = 0; s < n; ++s) {
        if (side[s] != -1) continue;
        vector<int> q = {s};
        side[s] = 0;
        for (int i = 0; i < q.size(); ++i) {
            for (int b : g[q[i]]) if (side[b] == -1) {
                side[b] = side[q[i]] ^ 1;
                q.push_back(b);
            }
        }
    }

    auto dfs = [&](auto &self, int a) -> bool {
        if (vis[a] == itr) return false;
        vis[a] = itr;
        for (int b : g[a]) if (match[b] == -1) {
            match[a] = b;
            match[b] = a;
            return true;
        }
        for (int b : g[a]) if (self(self, match[b])) {
            match[a] = b;
            match[b] = a;
            return true;
        }
        return false;
    };

    for (bool found = true; found; ++itr) {
        found = false;
        for (int a = 0; a < n; ++a) if (side[a] == 0 and match[a] == -1 and dfs(dfs, a)) {
            found = true;
        }
    }
    return match;
}
