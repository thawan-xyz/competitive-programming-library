// Kuhn's Algorithm: maximum bipartite matching
// Time: O(V * E) | Space: O(N + M)
// Note: connects left [0..n] to right [0..m] | match[right] returns left node or -1
vector<int> kuhn(int n, int m, vector<vector<int>> &g) {
    vector<int> match(m + 1, -1);
    int itr = 0;
    vector<int> v(n + 1);

    auto dfs = [&](auto &self, int a) -> bool {
        if (v[a] == itr) return false;
        v[a] = itr;
        for (int b : g[a]) if (match[b] == -1 or self(self, match[b])) {
            match[b] = a;
            return true;
        }
        return false;
    };

    for (int a = 0; a <= n; ++a, ++itr) {
        dfs(dfs, a);
    }
    return match;
}
