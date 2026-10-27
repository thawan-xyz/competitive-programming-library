// Steiner Tree: minimum cost to connect k terminal nodes in a graph of n nodes
// Time: O(3^k * n + 2^k * e log n) | Space: O(2^k * n)
// Note: assumes terminals are nodes 0 to k-1 | g is an adjacency list (node, weight)
// State: steiner[(1<<k)-1][i] = min cost to connect all k terminals and node i
vector<vector<int>> steiner_tree(const vector<vector<pair<int, int>>> &g, int k) {
    const int n = g.size();
    vector<vector<int>> steiner(1 << k, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) steiner[0][i] = 0;
    for (int i = 0; i < k; ++i) steiner[1 << i][i] = 0;
    for (int mask = 1; mask < (1 << k); ++mask) {
        for (int sub = mask; sub > 0; sub = mask & (sub - 1)) {
            for (int i = 0; i < n; ++i) {
                steiner[mask][i] = min(steiner[mask][i], steiner[sub][i] + steiner[mask ^ sub][i]);
            }
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int i = 0; i < n; ++i) if (steiner[mask][i] != inf) {
            pq.push({steiner[mask][i], i});
        }
        while (pq.size()) {
            auto [d, i] = pq.top(); pq.pop();
            if (steiner[mask][i] < d) continue;
            for (auto [j, w] : g[i]) if (steiner[mask][i] + w < steiner[mask][j]) {
                steiner[mask][j] = steiner[mask][i] + w;
                pq.push({steiner[mask][j], j});
            }
        }
    }
    return steiner;
}

// Steiner Tree: minimum cost to connect k terminal nodes in a graph of n nodes
// Time: O(3^k * n + 2^k * n^2) | Space: O(2^k * n)
// Note: assumes terminals are nodes 0 to k-1 | dist[u][v] must be the shortest path between u and v
// State: steiner[(1<<k)-1][i] = min cost to connect all k terminals and node i
vector<vector<int>> steiner_tree(const vector<vector<int>> &dist, int k) {
    const int n = dist.size();
    vector<vector<int>> steiner(1 << k, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) steiner[0][i] = 0;
    for (int i = 0; i < k; ++i) steiner[1 << i][i] = 0;
    for (int mask = 1; mask < (1 << k); ++mask) {
        for (int sub = mask; sub > 0; sub = mask & (sub - 1)) {
            for (int i = 0; i < n; ++i) {
                steiner[mask][i] = min(steiner[mask][i], steiner[sub][i] + steiner[mask ^ sub][i]);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                steiner[mask][j] = min(steiner[mask][j], steiner[mask][i] + dist[i][j]);
            }
        }
    }
    return steiner;
}
