vector<int> dijkstra(int s, vector<vector<pair<int, int>>> &g) {
    int n = g.size();
    vector<int> d(n, inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    d[s] = 0;
    pq.emplace(0, s);
    while (pq.size()) {
        auto [x, a] = pq.top(); pq.pop();
        if (d[a] < x) continue;
        for (auto [b, w] : g[a]) if (d[a] + w < d[b]) {
            d[b] = d[a] + w;
            pq.emplace(d[b], b);
        }
    }
    return d;
}
