// Steiner Tree: minimum cost to connect the terminals 0, ..., k - 1 in a weighted undirected graph
// Time: O(3^k n + 2^k m log m) | Space: O(2^k n)
// Note: steiner[mask][i] = min cost of a tree with the terminals in mask and node i
vector<vector<int>> steiner_tree(int k, vector<vector<pair<int, int>>> &g) {
    int n = g.size();
    vector<vector<int>> steiner(1 << k, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) steiner[0][i] = 0;
    for (int i = 0; i < k; ++i) steiner[1 << i][i] = 0;
    for (int mask = 1; mask < (1 << k); ++mask) {
        vector<int> &d = steiner[mask];
        for (int sub = (mask - 1) & mask; sub; sub = (sub - 1) & mask) {
            for (int i = 0; i < n; ++i) d[i] = min(d[i], steiner[sub][i] + steiner[mask ^ sub][i]);
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        for (int i = 0; i < n; ++i) if (d[i] != inf) pq.push({d[i], i});
        while (pq.size()) {
            auto [x, a] = pq.top(); pq.pop();
            if (d[a] < x) continue;
            for (auto [b, w] : g[a]) if (d[a] + w < d[b]) {
                d[b] = d[a] + w;
                pq.push({d[b], b});
            }
        }
    }
    return steiner;
}
