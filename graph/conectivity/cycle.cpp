vector<int> find_cycle(bool directed, vector<vector<int>> &g) {
    int n = g.size();
    vector<int> state(n), parent(n), cycle;

    auto dfs = [&](auto &self, int a, int p) -> bool {
        state[a] = 1;
        bool skip = not directed;
        for (int b : g[a]) {
            if (b == p and skip) {
                skip = false;
            } else if (state[b] == 0) {
                parent[b] = a;
                if (self(self, b, a)) return true;
            } else if (state[b] == 1) {
                for (int c = a; c != b; c = parent[c]) cycle.push_back(c);
                cycle.push_back(b);
                reverse(cycle.begin(), cycle.end());
                return true;
            }
        }
        state[a] = 2;
        return false;
    };

    for (int i = 0; i < n; ++i) if (state[i] == 0 and dfs(dfs, i, -1)) return cycle;
    return {};
}
