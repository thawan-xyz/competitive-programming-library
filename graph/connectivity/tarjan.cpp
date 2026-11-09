vector<int> tarjan(const vector<vector<int>> &g) {
    int n = g.size(), timer = 0, m = 0;
    vector<int> in(n, -1), low(n), comp(n, -1);
    vector<int> dfs, edge(n), path;
    for (int s = 0; s < n; ++s) if (in[s] == -1) {
        dfs = {s};
        while (dfs.size()) {
            int a = dfs.back();
            if (in[a] == -1) {
                in[a] = low[a] = timer++;
                path.push_back(a);
            }
            if (edge[a] < g[a].size()) {
                int b = g[a][edge[a]++];
                if (in[b] == -1) dfs.push_back(b);
                else if (comp[b] == -1) low[a] = min(low[a], in[b]);
                continue;
            }
            dfs.pop_back();
            if (dfs.size()) {
                low[dfs.back()] = min(low[dfs.back()], low[a]);
            }
            if (low[a] == in[a]) {
                while (comp[a] == -1) {
                    comp[path.back()] = m;
                    path.pop_back();
                }
                m++;
            }
        }
    }
    for (int &c : comp) c = m - 1 - c;
    return comp;
}

vector<vector<int>> condensed_graph(const vector<vector<int>> &g, const vector<int> &comp) {
    int m = *max_element(comp.begin(), comp.end()) + 1;
    vector<vector<int>> c(m);
    for (int a = 0; a < g.size(); ++a) {
        for (int b : g[a]) if (comp[a] != comp[b]) {
            c[comp[a]].push_back(comp[b]);
        }
    }
    for (auto &h : c) {
        sort(h.begin(), h.end());
        h.erase(unique(h.begin(), h.end()), h.end());
    }
    return c;
}
