struct edge {
    int a, b, w;
};

pair<bool, list<int>> bellman_ford(int n, int s, list<edge> &e) {
    list<int> d(n, inf);
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
