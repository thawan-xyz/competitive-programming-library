// Bidirectional BFS: shortest distance from s to t if it is at most k, always growing the smaller side by one layer
// Time: O(V + E) | Space: O(V)
// Note: undirected graph, returns -1 if the distance is more than k
int bidirectional_bfs(const vector<vector<int>> &g, int s, int t, int k) {
    if (s == t) return 0;
    vector<int> d1(g.size(), -1), d2(g.size(), -1);
    queue<int> q1, q2;
    d1[s] = d2[t] = 0, q1.push(s), q2.push(t);
    int best = k + 1;
    auto expand = [&]() {
        int size = q1.size();
        while (size--) {
            int a = q1.front();
            q1.pop();
            for (int b : g[a]) {
                if (d1[b] != -1 or d1[a] + 1 + d2[q2.front()] > k) continue;
                if (d2[b] != -1) best = min(best, d1[a] + 1 + d2[b]);
                else d1[b] = d1[a] + 1, q1.push(b);
            }
        }
    };
    while (q1.size() and q2.size()) {
        if (q1.size() > q2.size()) swap(q1, q2), swap(d1, d2);
        expand();
        if (best <= k) return best;
    }
    return -1;
}
