vector<int> centroid_decomposition(int r, vector<vector<int>> &g) {
    int n = g.size();
    vector<int> parent(n);
    vector<int> size(n);
    vector<bool> removed(n);
    auto dfs = [&](auto &self, int a, int p) -> int {
        size[a] = 1;
        for (int b : g[a]) if (b != p and not removed[b]) {
            size[a] += self(self, b, a);
        }
        return size[a];
    };
    auto centroid = [&](auto &self, int a, int p, int s) -> int {
        for (int b : g[a]) if ((b != p and not removed[b]) and size[b] > s / 2) {
            return self(self, b, a, s);
        }
        return a;
    };
    auto build = [&](auto &self, int a, int p) -> void {
        int s = dfs(dfs, a, a);
        int c = centroid(centroid, a, a, s);
        parent[c] = p;
        removed[c] = true;
        for (int b : g[c]) if (not removed[b]) {
            self(self, b, c);
        }
    };
    build(build, r, -1);
    return parent;
}
