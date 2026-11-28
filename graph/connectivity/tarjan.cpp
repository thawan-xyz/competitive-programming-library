vector<int> tarjan(const vector<vector<int>> &g, bool undirected) {
    int n = g.size(), timer = 0, m = 0;
    vector<int> in(n, -1), low(n), comp(n, -1), path;
    auto dfs = [&](auto &dfs, int a, int p) -> void {
        in[a] = low[a] = timer++;
        path.push_back(a);
        bool skip = undirected;
        for (int b : g[a]) {
            if (b == p and skip) skip = false;
            else if (in[b] == -1) dfs(dfs, b, a), low[a] = min(low[a], low[b]);
            else if (comp[b] == -1) low[a] = min(low[a], in[b]);
        }
        if (low[a] == in[a]) {
            while (comp[a] == -1) comp[path.back()] = m, path.pop_back();
            m++;
        }
    };
    for (int a = 0; a < n; ++a) if (in[a] == -1) dfs(dfs, a, -1);
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
