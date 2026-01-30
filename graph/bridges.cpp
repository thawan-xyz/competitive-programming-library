list<pair<int, int>> bridges(list<list<int>> &graph) {
    int n = graph.size() - 1, timer = 1;
    list<int> in(n + 1), low(n + 1);
    list<pair<int, int>> edges;

    function<void(int, int)> dfs = [&](int a, int p) -> void {
        in[a] = low[a] = timer++;
        for (int b : graph[a]) if (b != p) {
            if (in[b] != 0) {
                low[a] = min(low[a], in[b]);
            } else {
                dfs(b, a);
                low[a] = min(low[a], low[b]);
                if (in[a] < low[b]) edges.push_back({a, b});
            }
        }
    };

    for (int i = 1; i <= n; ++i) if (in[i] == 0) dfs(i, 0);
    return edges;
}
