list<list<int>> tarjan(list<list<int>> &graph) {
    int n = graph.size() - 1, timer = 1;
    list<list<int>> components;
    list<int> in(n + 1), low(n + 1);
    stack<int> trail;
    list<bool> inside(n + 1);

    function<void(int)> dfs = [&](int a) -> void {
        in[a] = low[a] = timer++;
        trail.push(a);
        inside[a] = true;
        for (int b : graph[a]) {
            if (in[b] == 0) {
                dfs(b);
                low[a] = min(low[a], low[b]);
            } else if (inside[b]) {
                low[a] = min(low[a], in[b]);
            }
        }

        if (in[a] == low[a]) {
            list<int> component;
            while (true) {
                int b = trail.top(); trail.pop();
                inside[b] = false;
                component.push_back(b);
                if (b == a) break;
            }
            components.push_back(component);
        }
    };

    for (int i = 1; i <= n; ++i) if (in[i] == 0) dfs(i);
    reverse(components.begin(), components.end());
    return components;
}
