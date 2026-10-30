// Centroid Decomposition: parts[c] = parts left after removing the centroid c, as lists of (v, d = distance from v to c)
// Time: O(N log N) | Space: O(N log N)
// Note: centroid_ancestors(parts) gives anc[v] = centroid ancestors (c, d) of v, from (v, 0) up to the root
vector<vector<vector<pair<int, int>>>> centroid_decomposition(const vector<vector<int>> &g) {
    int n = g.size();
    vector<int> p(n), size(n);
    vector<bool> rem(n);
    vector<vector<vector<pair<int, int>>>> parts(n);
    auto bfs = [&](int r, int h) -> vector<pair<int, int>> {
        vector<pair<int, int>> q = {{r, 1}};
        p[r] = h;
        for (int i = 0; i < q.size(); ++i) {
            auto [a, d] = q[i];
            size[a] = 1;
            for (int b : g[a]) if (b != p[a] and not rem[b]) {
                p[b] = a;
                q.push_back({b, d + 1});
            }
        }
        for (int i = q.size() - 1; i > 0; --i) size[p[q[i].first]] += size[q[i].first];
        return q;
    };
    auto build = [&](auto &self, const vector<pair<int, int>> &q) -> void {
        int c = q[0].first;
        for (auto [a, d] : q) if (2 * size[a] > q.size()) c = a;
        rem[c] = true;
        for (int b : g[c]) if (not rem[b]) parts[c].push_back(bfs(b, c));
        for (auto &part : parts[c]) self(self, part);
    };
    for (int a = 0; a < n; ++a) if (not rem[a]) build(build, bfs(a, -1));
    return parts;
}

vector<vector<pair<int, int>>> centroid_ancestors(const vector<vector<vector<pair<int, int>>>> &parts) {
    int n = parts.size();
    vector<pair<int, int>> ord;
    for (int c = 0; c < n; ++c) {
        int s = 1;
        for (auto &part : parts[c]) s += part.size();
        ord.push_back({s, c});
    }
    sort(ord.begin(), ord.end());
    vector<vector<pair<int, int>>> anc(n);
    for (auto [s, c] : ord) {
        anc[c].push_back({c, 0});
        for (auto &part : parts[c]) for (auto [v, d] : part) anc[v].push_back({c, d});
    }
    return anc;
}
