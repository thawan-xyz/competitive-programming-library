list<pair<int, int>> bridges(list<list<int>> &graph) {
    int n = graph.size() - 1, timer = 1;
    list<pair<int, int>> edges;
    list<int> id(n + 1), low(n + 1);

    function<void(int, int)> dfs = [&](int a, int p) -> void {
        id[a] = low[a] = timer++;
        for (int b : graph[a]) if (b != p) {
            if (id[b] != 0) {
                low[a] = min(low[a], id[b]);
            } else {
                dfs(b, a);
                low[a] = min(low[a], low[b]);
                if (low[b] > id[a]) edges.push_back({a, b});
            }
        }
    };

    for (int i = 1; i <= n; ++i) if (id[i] == 0) dfs(i, 0);
    return edges;
}
