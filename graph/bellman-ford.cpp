struct edge {
    int a, b, w;
};

pair<bool, vector<int>> bellman_ford(int s, int n, vector<edge> &e) {
    vector<int> d(n + 1, inf);
    d[s] = 0;
    for (int i = 1; i < n; ++i) {
        bool changed = false;
        for (auto &[a, b, w] : e) if (d[a] != inf and d[a] + w < d[b]) {
            d[b] = d[a] + w;
            changed = true;
        }
        if (not changed) break;
    }
    for (auto &[a, b, w] : e) if (d[a] != inf and d[a] + w < d[b]) {
        return {true, d};
    }
    return {false, d};
}

pair<bool, vector<int>> shortest_path_faster_algorithm(int s, int n, vector<vector<pair<int, int>>> &g) {
    vector<int> d(n + 1, inf);
    vector<int> c(n + 1);
    queue<int> q;
    vector<bool> in(n + 1);
    d[s] = 0;
    q.push(s);
    in[s] = true;
    while (q.size()) {
        int a = q.front(); q.pop();
        in[a] = false;
        for (auto &[b, w] : g[a]) if (d[a] + w < d[b]) {
            d[b] = d[a] + w;
            if (not in[b]) {
                if (++c[b] >= n) return {true, d};
                q.push(b);
                in[b] = true;
            }
        }
    }
    return {false, d};
}
