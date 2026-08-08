vector<vector<int>> block_cut_tree(vector<vector<int>> &g) {
    int n = g.size(), t = 0;
    vector<int> tin(n, -1), low(n), st;
    vector<vector<int>> bct(n);
    auto dfs = [&](auto &self, int a, int p) -> void {
        tin[a] = low[a] = t++;
        st.push_back(a);
        for (int b : g[a]) if (b != p) {
            if (tin[b] != -1) {
                low[a] = min(low[a], tin[b]);
            } else {
                self(self, b, a);
                low[a] = min(low[a], low[b]);
                if (tin[a] <= low[b]) {
                    int i = bct.size();
                    bct.emplace_back();
                    bct[i].push_back(a);
                    bct[a].push_back(i);
                    while (true) {
                        int c = st.back(); st.pop_back();
                        bct[i].push_back(c);
                        bct[c].push_back(i);
                        if (b == c) break;
                    }
                }
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        if (tin[i] == -1) {
            dfs(dfs, i, i);
        }
    }
    return bct;
}
