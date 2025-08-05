array<pair<int, int>> bridges(array<array<int>> &graph) {
    int n = graph.size() - 1, timer = 1;
    array<pair<int, int>> edges;
    array<int> id(n + 1), rank(n + 1);

    function<void(int, int)> dfs = [&](int a, int p) -> void {
        id[a] = rank[a] = timer++;
        bool skip = true;
        for (int b : graph[a]) {
            if (p == b and skip) {
                skip = false;
            } else if (id[b] != 0) {
                rank[a] = min(rank[a], id[b]);
            } else {
                dfs(b, a);
                rank[a] = min(rank[a], rank[b]);
                if (rank[b] > id[a]) edges.push_back({a, b});
            }
        }
    };

    for (int i = 1; i <= n; ++i) if (id[i] == 0) dfs(i, 0);
    return edges;
}
