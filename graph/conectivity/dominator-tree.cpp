struct dominator_dsu {
    vector<int> p, c;
    vector<int> &x;

    dominator_dsu(int n, vector<int> &x): p(n), c(n), x(x) {
        iota(p.begin(), p.end(), 0);
        iota(c.begin(), c.end(), 0);
    }

    int find(int a) {
        if (p[a] == a) return c[a];
        int r = p[a];
        if (p[r] != r) {
            find(r);
            if (x[c[r]] < x[c[a]]) c[a] = c[r];
            p[a] = p[r];
        }
        return c[a];
    }

    void unite(int a, int b) {
        p[b] = a;
    }
};

vector<vector<int>> dominator_tree(int s, vector<vector<int>> &g) {
    int n = g.size();
    vector<int> tin(n, -1), inv(n), parent(n);
    int t = 0;
    auto dfs = [&](auto &self, int a) -> void {
        tin[a] = t;
        inv[t] = a;
        t++;
        for (int b : g[a]) if (tin[b] == -1) {
            parent[b] = a;
            self(self, b);
        }
    };
    dfs(dfs, s);
    vector<vector<int>> rev(n);
    for (int a = 0; a < n; ++a) {
        for (int b : g[a]) rev[b].push_back(a);
    }
    vector<int> semi(n), dom(n);
    for (int a = 0; a < n; ++a) semi[a] = tin[a];
    vector<vector<int>> bucket(n);
    dominator_dsu dsu(n, semi);
    for (int i = t - 1; t >= 1; --i) {
        int a = inv[i];
        for (int b : rev[a]) if (tin[b] != -1) {
            semi[a] = min(semi[a], semi[dsu.find(b)]);
        }
        bucket[inv[semi[a]]].push_back(a);
        int p = parent[a];
        dsu.unite(p, a);
        for (int b : bucket[p]) {
            dom[b] = p;
            int c = dsu.find(b);
            if (semi[c] < semi[b]) dom[b] = c;
        }
        bucket[p].clear();
    }
    vector<vector<int>> dt(n);
    for (int i = 1; i < t; ++i) {
        int a = inv[i];
        if (dom[a] != inv[semi[a]]) dom[a] = dom[dom[a]];
        dt[dom[a]].push_back(a);
    }
    return dt;
}
