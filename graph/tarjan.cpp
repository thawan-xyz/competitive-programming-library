list<list<int>> tarjan(list<list<int>> &g, bool one_based) {
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

    for (int a = one_based; a < n; ++a) {
        if (id[a] == 0) {
            dfs(dfs, a);
        }
    }

    reverse(components.begin(), components.end());
    return components;
}

pair<list<list<int>>, list<int>> condensed_graph(list<list<int>> &g, bool one_based) {
    int n = g.size();
    list<list<int>> components = tarjan(g, one_based);
    int m = components.size();

    list<int> id(n);
    for (int i = 0; i < m; ++i) {
        for (int a : components[i]) {
            id[a] = i;
        }
    }

    list<list<int>> c(m);
    for (int a = one_based; a < n; ++a) {
        for (int b : g[a]) if (id[a] != id[b]) {
            c[id[a]].push_back(id[b]);
        }
    }

    for (int i = 0; i < m; ++i) {
        sort(c[i].begin(), c[i].end());
        c[i].erase(unique(c[i].begin(), c[i].end()), c[i].end());
    }
    return {c, id};
}
