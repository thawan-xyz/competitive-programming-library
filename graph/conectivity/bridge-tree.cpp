pair<vector<vector<int>>, vector<int>> bridge_tree(vector<vector<int>> &g) {
    int n = g.size(), t = 0;
    vector<int> tin(n, -1), low(n), comp(n), st;
    vector<vector<int>> bt;
    auto dfs = [&](auto &self, int a, int p) -> void {
        tin[a] = low[a] = t++;
        st.push_back(a);
        bool parent = true;
        for (int b : g[a]) {
            if (b == p and parent) {
                parent = false;
                continue;
            }
            if (tin[b] != -1) {
                low[a] = min(low[a], tin[b]);
            } else {
                self(self, b, a);
                low[a] = min(low[a], low[b]);
            }
        }
        if (low[a] == tin[a]) {
            int i = bt.size();
            bt.emplace_back();
            while (true) {
                int c = st.back(); st.pop_back();
                comp[c] = i;
                if (c == a) break;
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        if (tin[i] == -1) {
            dfs(dfs, i, -1);
        }
    }
    for (int a = 0; a < n; ++a) {
        for (int b : g[a]) {
            if (comp[a] != com[b]) {
                tree[comp[a]].push_back(tree[comp[b]]);
            }
        }
    }
}
