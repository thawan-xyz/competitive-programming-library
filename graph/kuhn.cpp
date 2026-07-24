// Kuhn's Algorithm: maximum bipartite matching
// Time: O(V * E) | Space: O(N + M)
// Note: connects left [0..n] to right [0..m] | match[right] returns left node or -1
vector<int> kuhn(int n, int m, vector<vector<int>> &g) {
    vector<int> match(m + 1, -1);
    vector<bool> v(n + 1);

    auto dfs = [&](auto &self, int a) -> bool {
        if (v[a]) return false;
        v[a] = true;
        for (int b : g[a]) if (match[b] == -1 or self(self, match[b])) {
            match[b] = a;
            return true;
        }
        return false;
    };

    for (int a = 0; a <= n; ++a) {
        fill(v.begin(), v.end(), false);
        dfs(dfs, a);
    }
    return match;
}
