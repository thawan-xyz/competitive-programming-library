// Bidirectional Dijkstra: shortest distance from s to t if it is at most k, always growing the side with the smaller heap
// Time: O((V + E) log V) | Space: O(V + E)
// Note: undirected graph with weights >= 0, returns -1 if the distance is more than k
int bidirectional_dijkstra(const vector<vector<pair<int, int>>> &g, int s, int t, int k) {
    if (s == t) return 0;
    vector<int> d1(g.size(), inf), d2(g.size(), inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q1, q2;
    d1[s] = d2[t] = 0, q1.push({0, s}), q2.push({0, t});
    int best = k + 1;
    auto expand = [&]() {
        auto [da, a] = q1.top();
        q1.pop();
        if (da > d1[a]) return;
        for (auto [b, w] : g[a]) {
            if (d1[b] <= da + w or da + w + q2.top().first > k) continue;
            d1[b] = da + w, q1.push({d1[b], b});
            if (d2[b] != inf) best = min(best, d1[b] + d2[b]);
        }
    };
    while (q1.size() and q2.size() and q1.top().first + q2.top().first < best) {
        if (q1.size() > q2.size()) swap(q1, q2), swap(d1, d2);
        expand();
    }
    return best <= k ? best : -1;
}
