list<list<int>> tarjan(list<list<int>> &g, bool one) {
    int n = g.size(), timer = 1;
    list<list<int>> components;
    list<int> id(n), low(n);
    stack<int> trail;
    list<bool> in(n);

    auto dfs = [&](auto &&self, int a) -> void {
        id[a] = low[a] = timer++;
        trail.push(a);
        in[a] = true;
        for (int b : g[a]) {
            if (id[b] == 0) {
                self(self, b);
                low[a] = min(low[a], low[b]);
            } else if (in[b]) {
                low[a] = min(low[a], id[b]);
            }
        }

        if (id[a] == low[a]) {
            list<int> component;
            while (true) {
                int b = trail.top(); trail.pop();
                in[b] = false;
                component.push_back(b);
                if (b == a) break;
            }
            components.push_back(component);
        }
    };

    for (int i = one; i < n; ++i) {
        if (id[i] == 0) {
            dfs(dfs, i);
        }
    }

    reverse(components.begin(), components.end());
    return components;
}
