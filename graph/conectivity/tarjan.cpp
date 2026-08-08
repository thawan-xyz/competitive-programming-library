vector<vector<int>> tarjan(int r, vector<vector<int>> &g) {
    int n = g.size(), timer = 1;
    vector<vector<int>> components;
    vector<int> id(n), low(n);
    stack<int> trail;
    vector<bool> in(n);

    auto dfs = [&](auto &self, int a) -> void {
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
            vector<int> component;
            while (true) {
                int b = trail.top(); trail.pop();
                in[b] = false;
                component.push_back(b);
                if (b == a) break;
            }
            components.push_back(component);
        }
    };

    for (int a = r; a < n; ++a) {
        if (id[a] == 0) {
            dfs(dfs, a);
        }
    }

    reverse(components.begin(), components.end());
    return components;
}

pair<vector<vector<int>>, vector<int>> condensed_graph(int r, vector<vector<int>> &g) {
    int n = g.size();
    vector<vector<int>> components = tarjan(r, g);
    int m = components.size();

    vector<int> id(n);
    for (int i = 0; i < m; ++i) {
        for (int a : components[i]) {
            id[a] = i;
        }
    }

    vector<vector<int>> c(m);
    for (int a = r; a < n; ++a) {
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
