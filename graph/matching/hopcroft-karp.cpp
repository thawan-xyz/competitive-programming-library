// Hopcroft-Karp: maximum bipartite matching, augmenting along shortest paths in phases
// Time: O(E sqrt(V)) | Space: O(V + E)
// Note: g[a] has the right neighbors of left vertex a | returns match[b], the left vertex of b or -1, for b up to the largest right vertex
vector<int> hopcroft_karp(vector<vector<int>> &g) {
    int n = g.size(), m = 0, lim = -1;
    for (int a = 0; a < n; ++a) for (int b : g[a]) m = max(m, b + 1);
    vector<int> match(m, -1), d(n), itr(n);
    vector<bool> used(n);

    auto bfs = [&]() -> bool {
        queue<int> q;
        for (int a = 0; a < n; ++a) {
            d[a] = -1;
            if (not used[a]) d[a] = 0, q.push(a);
        }
        lim = -1;
        while (q.size()) {
            int a = q.front(); q.pop();
            if (lim != -1 and d[a] >= lim) continue;
            for (int b : g[a]) {
                int c = match[b];
                if (c == -1 and lim == -1) lim = d[a] + 1;
                if (c != -1 and d[c] == -1) d[c] = d[a] + 1, q.push(c);
            }
        }
        return lim != -1;
    };

    auto dfs = [&](auto &self, int a) -> bool {
        for (int &i = itr[a]; i < g[a].size(); ++i) {
            int b = g[a][i], c = match[b];
            if (c == -1 and d[a] + 1 != lim) continue;
            if (c == -1 or (d[c] == d[a] + 1 and self(self, c))) return used[a] = true, match[b] = a, true;
        }
        return d[a] = -1, false;
    };

    while (bfs()) {
        fill(itr.begin(), itr.end(), 0);
        for (int a = 0; a < n; ++a) if (not used[a]) dfs(dfs, a);
    }
    return match;
}
