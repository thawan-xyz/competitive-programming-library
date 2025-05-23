void tarjan() {
    int timer = 0;
    array<array<int>> graph;
    array<int> tin, low;
    array<bool> visited, articulation;
    array<pair<int, int>> bridges;

    function<void(int, int)> dfs = [&](int a, int p) -> void {
        visited[a] = true;
        tin[a] = low[a] = timer++;

        for (int b : graph[a]) {
            if (b == p) continue;

            if (visited[b]) {
                low[a] = min(low[a], tin[b]);
            } else {
                dfs(b, a);
                low[a] = min(low[a], low[b]);
                
                if (tin[a] < low[b]) bridges.emplace_back(a, b);
                if (p != -1 and tin[a] <= low[b]) articulation[a] = true;
            }
        }
        if (p == -1 and graph[a].size() > 1) articulation[a] = true;
    };
}

array<array<int>> tarjan(int n, graph &g) {
    int timer = 0, total = 0;
    array<int> tin(n, -1), low(n, -1), id(n);
    stack<int> helper;
    array<bool> stack(n);
    array<array<int>> components;

    function<void(int)> dfs = [&](int a) {
        tin[a] = low[a] = timer++;
        stack[a] = true;
        helper.push(a);

        for (int b : g[a]) {
            if (tin[b] == -1) {
                dfs(b);
                low[a] = min(low[a], low[b]);
            } else if (stack[b]) {
                low[a] = min(low[a], tin[b]);
            }
        }

        if (tin[a] == low[a]) {
            array<int> component;
            int b;
            do {
                b = helper.top(); helper.pop();
                stack[b] = false;
                id[b] = total;
                component.push_back(b);
            } while (b != a);

            components.push_back(component);
            total++;
        }
    };

    for (int i = 0; i < n; ++i) if (tin[i] == -1) dfs(i);
    return components;
}
