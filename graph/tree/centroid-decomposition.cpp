pair<vector<int>, vector<vector<int>>> centroid_decomposition(int r, vector<vector<int>> &g) {
    int n = g.size();
    vector<int> parent(n);
    vector<int> size(n);
    vector<bool> removed(n);
    vector<vector<int>> dist(n);
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
    auto distance = [&](auto &self, int a, int p, int d) -> void {
        dist[a].push_back(d);
        for (int b : g[a]) if (b != p and not removed[b]) {
            self(self, b, a, d + 1);
        }
    };
    auto build = [&](auto &self, int a, int p) -> void {
        int s = dfs(dfs, a, a);
        a = centroid(centroid, a, a, s);
        distance(distance, a, a, 0);
        parent[a] = p;
        removed[a] = true;
        for (int b : g[a]) if (not removed[b]) {
            self(self, b, a);
        }
    };
    build(build, r, -1);
    for (auto &path : dist) reverse(path.begin(), path.end());
    return {parent, dist};
}
