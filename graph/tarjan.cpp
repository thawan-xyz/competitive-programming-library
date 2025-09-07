array<array<int>> tarjan(array<array<int>> &graph) {
    int n = graph.size() - 1, timer = 1;
    array<array<int>> components;
    array<int> id(n + 1), low(n + 1);
    stack<int> trail;
    array<bool> inside(n + 1);

    function<void(int)> dfs = [&](int a) -> void {
        id[a] = low[a] = timer++;
        trail.push(a);
        inside[a] = true;
        for (int b : graph[a]) {
            if (id[b] == 0) dfs(b);
            if (inside[b]) low[a] = min(low[a], low[b]);
        }

        if (id[a] == low[a]) {
            array<int> component;
            int b = 0;
            do {
                b = trail.top();
                trail.pop();
                inside[b] = false;
                component.push_back(b);
            } while (b != a);
            components.push_back(component);
        }
    };

    for (int i = 1; i <= n; ++i) if (id[i] == 0) dfs(i);
    return components;
}
