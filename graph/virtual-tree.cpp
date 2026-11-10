// Virtual Tree: compresses the tree to the given vertices and their lcas, at most 2k - 1 vertices
// Time: O(N log N) build, O(1) lca, O(k log k) per compression | Space: O(N log N)
// Note: build(v) returns {u, p} sorted by tin, with p = -1 at the root of the compressed tree | edge p-u is a path of depth[u] - depth[p] edges
struct virtual_tree {
    vector<int> tin, depth;
    vector<vector<int>> table;

    virtual_tree(vector<vector<int>> &g, int root): tin(g.size()), depth(g.size()) {
        int n = g.size(), t = 0;
        table.assign(__lg(n) + 1, vector<int>(n));
        auto dfs = [&](auto &self, int a, int p) -> void {
            tin[a] = t, table[0][t++] = p;
            for (int b : g[a]) if (b != p) depth[b] = depth[a] + 1, self(self, b, a);
        };
        dfs(dfs, root, root);
        for (int j = 1; j < table.size(); ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) table[j][i] = first(table[j - 1][i], table[j - 1][i + (1 << (j - 1))]);
        }
    }

    int first(int a, int b) {
        return tin[a] < tin[b] ? a : b;
    }

    int lca(int a, int b) {
        if (a == b) return a;
        if (tin[a] > tin[b]) swap(a, b);
        int l = tin[a] + 1, r = tin[b] + 1, j = __lg(r - l);
        return first(table[j][l], table[j][r - (1 << j)]);
    }

    int dist(int a, int b) {
        return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    }

    vector<pair<int, int>> build(vector<int> v) {
        auto cmp = [&](int a, int b) { return tin[a] < tin[b]; };
        sort(v.begin(), v.end(), cmp);
        for (int i = v.size() - 1; i > 0; --i) v.push_back(lca(v[i - 1], v[i]));
        sort(v.begin(), v.end(), cmp);
        v.erase(unique(v.begin(), v.end()), v.end());
        vector<pair<int, int>> res = {{v[0], -1}};
        for (int i = 1; i < v.size(); ++i) res.push_back({v[i], lca(v[i - 1], v[i])});
        return res;
    }
};
