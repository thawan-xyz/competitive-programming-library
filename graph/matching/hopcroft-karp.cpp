// Hopcroft-Karp: maximum matching in a bipartite graph, augmenting along shortest paths in phases
// Time: O(E sqrt(V)) | Space: O(V + E)
// Note: returns match[a], the vertex matched with a or -1
vector<int> hopcroft_karp(vector<vector<int>> &g) {
    int n = g.size(), lim = -1;
    vector<int> match(n, -1), d(n), itr(n), side(n, -1);
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

    auto bfs = [&]() -> bool {
        queue<int> q;
        for (int a = 0; a < n; ++a) {
            d[a] = -1;
            if (side[a] == 0 and match[a] == -1) d[a] = 0, q.push(a);
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
            if (c == -1 or (d[c] == d[a] + 1 and self(self, c))) {
                match[a] = b;
                match[b] = a;
                return true;
            }
        }
        return d[a] = -1, false;
    };

    while (bfs()) {
        fill(itr.begin(), itr.end(), 0);
        for (int a = 0; a < n; ++a) if (side[a] == 0 and match[a] == -1) {
            dfs(dfs, a);
        }
    }
    return match;
}
