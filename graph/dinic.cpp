struct dinic {
    struct edge {
        int b, w, i;
        bool h;
    };

    int n;
    vector<vector<edge>> g;
    vector<int> l, p;

    dinic(int n): n(n), g(n), l(n), p(n) {}

    void directed(int a, int b, int w) {
        g[a].push_back({b, w, static_cast<int>(g[b].size()), true});
        g[b].push_back({a, 0, static_cast<int>(g[a].size()) - 1, false});
    }

    void undirected(int a, int b, int w) {
        g[a].push_back({b, w, static_cast<int>(g[b].size()), true});
        g[b].push_back({a, w, static_cast<int>(g[a].size()) - 1, true});
    }

    bool bfs(int s, int t) {
        fill(l.begin(), l.end(), -1);
        l[s] = 0;
        queue<int> q;
        q.push(s);

        while (not q.empty()) {
            int a = q.front(); q.pop();
            for (auto &[b, w, i, h] : g[a]) {
                if (w > 0 and l[b] < 0) {
                    l[b] = l[a] + 1;
                    q.push(b);
                }
            }
        }
        return l[t] >= 0;
    }

    int dfs(int a, int t, int f) {
        if (a == t or f == 0) return f;

        for (int &k = p[a]; k < g[a].size(); ++k) {
            auto &[b, w, i, h] = g[a][k];
            if (w > 0 and l[b] == l[a] + 1) {
                if (int d = dfs(b, t, min(f, w))) {
                    w -= d;
                    g[b][i].w += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int flow(int s, int t) {
        int f = 0;
        while (bfs(s, t)) {
            fill(p.begin(), p.end(), 0);
            int d = 0;
            while (d = dfs(s, t, inf)) {
                f += d;
            }
        }
        return f;
    }

    bool on_cut(int a) {
        return l[a] >= 0;
    }

    vector<pair<int, int>> saturated_edges() {
        vector<pair<int, int>> e;
        for (int a = 0; a < n; ++a) {
            for (auto [b, w, i, h] : g[a]) if (h and w == 0) {
                e.push_back({a, b});
            }
        }
        return e;
    }
};
