vector<int> find_cycle(bool one, bool is_directed, vector<vector<int>> &g) {
    int n = g.size();
    vector<int> state(n), parent(n);
    vector<int> cycle;
    auto dfs = [&](auto &self, int a, int p) -> bool {
        state[a] = 1;
        for (int b : g[a]) if (b != p or is_directed) {
            if (state[b] == 0) {
                parent[b] = a;
                if (self(self, b, a)) return true;
            } else if (state[b] == 1) {
                int c = a;
                while (c != b) {
                    cycle.push_back(c);
                    c = parent[c];
                }
                cycle.push_back(b);
                reverse(cycle.begin(), cycle.end());
                return true;
            }
        }
        state[a] = 2;
        return false;
    };
    for (int i = one; i < n; ++i) if (state[i] == 0) {
        if (dfs(dfs, i, -1)) return cycle;
    }
    return {};
}
