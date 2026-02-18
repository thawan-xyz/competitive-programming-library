struct edge {
    int a, b, w;
};

pair<bool, list<int>> bellman_ford(int s, int n, list<edge> &e) {
    list<int> d(n + 1, inf);
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

pair<bool, list<int>> shortest_path_faster_algorithm(int s, int n, list<list<pair<int, int>>> &g) {
    list<int> d(n + 1, inf);
    list<int> c(n + 1);
    queue<int> q;
    list<bool> in(n + 1);
    d[s] = 0;
    q.push(s);
    in[s] = true;
    while (q.size()) {
        int a = q.front(); q.pop();
        in[a] = false;
        for (auto &[b, w] : g[a]) if (d[a] + w < d[b]) {
            d[b] = d[a] + w;
            if (not in[b]) {
                if (++c[b] == n) return {true, d};
                q.push(b);
                in[b] = true;
            }
        }
    }
    return {false, d};
}
