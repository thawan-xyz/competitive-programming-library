vector<int> bellman_ford(int s, int n, vector<array<int, 3>> &e) {
    vector<int> d(n, inf);
    d[s] = 0;
    for (int i = 1; i < n; ++i) {
        bool chd = false;
        for (auto [a, b, w] : e) if (d[a] != inf and d[a] + w < d[b]) {
            d[b] = d[a] + w;
            chd = true;
        }
        if (not chd) break;
    }
    for (auto [a, b, w] : e) if (d[a] != inf and d[a] + w < d[b]) return {};
    return d;
}

vector<int> shortest_path_faster_algorithm(int s, vector<vector<pair<int, int>>> &g) {
    int n = g.size();
    vector<int> d(n, inf), c(n);
    vector<bool> in(n);
    queue<int> q;
    d[s] = 0;
    in[s] = true;
    q.push(s);
    while (q.size()) {
        int a = q.front(); q.pop();
        in[a] = false;
        for (auto [b, w] : g[a]) if (d[a] + w < d[b]) {
            d[b] = d[a] + w;
            if (not in[b]) {
                c[b] += 1;
                if (c[b] >= n) return {};
                in[b] = true;
                q.push(b);
            }
        }
    }
    return d;
}
