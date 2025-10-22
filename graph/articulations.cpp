list<int> articulations(list<list<int>> &graph) {
    int n = graph.size() - 1, timer = 1;
    list<int> id(n + 1), low(n + 1);
    list<int> points;
    list<bool> is_articulation(n + 1);

    function<void(int, int)> dfs = [&](int a, int p) -> void {
        id[a] = low[a] = timer++;
        int children = 0;
        for (int b : graph[a]) if (b != p) {
            if (id[b] != 0) {
                low[a] = min(low[a], id[b]);
            } else {
                children++;
                dfs(b, a);
                low[a] = min(low[a], low[b]);
                if (low[b] >= id[a]) is_articulation[a] = true;
            }
        }
        if (p == 0) is_articulation[a] = children > 1;
    };

    for (int i = 1; i <= n; ++i) if (id[i] == 0) dfs(i, 0);
    for (int i = 1; i <= n; ++i) if (is_articulation[i]) points.push_back(i);
    return points;
}
