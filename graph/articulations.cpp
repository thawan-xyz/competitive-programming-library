list<int> articulations(list<list<int>> &graph) {
    int n = graph.size() - 1, timer = 1;
    list<int> in(n + 1), low(n + 1);
    list<bool> articulation(n + 1);
    list<int> points;

    function<void(int, int)> dfs = [&](int a, int p) -> void {
        in[a] = low[a] = timer++;
        int children = 0;
        for (int b : graph[a]) if (b != p) {
            if (in[b] != 0) {
                low[a] = min(low[a], in[b]);
            } else {
                children++;
                dfs(b, a);
                low[a] = min(low[a], low[b]);
                if (low[b] >= in[a]) articulation[a] = true;
            }
        }
        if (p == 0) articulation[a] = children > 1;
    };

    for (int i = 1; i <= n; ++i) if (in[i] == 0) dfs(i, 0);
    for (int i = 1; i <= n; ++i) if (articulation[i]) points.push_back(i);
    return points;
}
