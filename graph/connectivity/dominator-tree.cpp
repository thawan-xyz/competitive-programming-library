// Dominator Tree: a dominates b if every path from s to b passes through a, the tree links each vertex to its closest dominator
// Time: O((V + E) log V) | Space: O(V + E)
// Note: returns the children of each vertex in the tree rooted at s | vertices not reachable from s are left out
vector<vector<int>> dominator_tree(int s, vector<vector<int>> &g) {
    int n = g.size();
    vector<int> tin(n, -1), order, parent(n), semi(n), idom(n), anc(n), best(n);
    vector<vector<int>> rev(n), bucket(n);
    auto dfs = [&](auto &self, int a) -> void {
        tin[a] = order.size(), order.push_back(a);
        for (int b : g[a]) {
            rev[b].push_back(a);
            if (tin[b] == -1) parent[b] = a, self(self, b);
        }
    };
    dfs(dfs, s);
    auto find = [&](auto &self, int a) -> int {
        int p = anc[a];
        if (anc[p] != p) {
            self(self, p);
            if (semi[best[p]] < semi[best[a]]) best[a] = best[p];
            anc[a] = anc[p];
        }
        return best[a];
    };
    for (int a = 0; a < n; ++a) semi[a] = tin[a], anc[a] = best[a] = a;
    for (int i = order.size() - 1; i > 0; --i) {
        int a = order[i], p = parent[a];
        for (int b : rev[a]) semi[a] = min(semi[a], semi[find(find, b)]);
        bucket[order[semi[a]]].push_back(a);
        anc[a] = p;
        for (int b : bucket[p]) {
            int c = find(find, b);
            idom[b] = semi[c] < semi[b] ? c : p;
        }
        bucket[p].clear();
    }
    vector<vector<int>> tree(n);
    for (int i = 1; i < order.size(); ++i) {
        int a = order[i];
        if (idom[a] != order[semi[a]]) idom[a] = idom[idom[a]];
        tree[idom[a]].push_back(a);
    }
    return tree;
}
