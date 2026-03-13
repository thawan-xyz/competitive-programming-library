struct dinic {
    int n;
    vector<vector<array<int, 3>>> g;
    vector<int> l, p;

    dinic(int n): n(n), g(n), l(n), p(n) {}

    void insert(int a, int b, int w) {
        g[a].push_back({b, w, g[b].size()});
        g[b].push_back({a, 0, g[a].size() - 1});
    }

    bool bfs(int s, int t) {
        fill(l.begin(), l.end(), -1);
        l[s] = 0;
        queue<int> q;
        q.push(s);

        while (not q.empty()) {
            int a = q.front(); q.pop();
            for (auto &[b, w, i] : g[a]) {
                if (w > 0 and l[b] < 0) {
                    l[b] = l[a] + 1;
                    q.push(b);
                }
            }
        }
        return l[t] >= 0;
    }

    int dfs(int a, int t, int f) {
        if (a == t) return f;

        for (int &k = p[a]; k < g[a].size(); ++k) {
            auto &[b, w, i] = g[a][k];
            if (w > 0 and l[b] == l[a] + 1) {
                int d = 0;
                if ((d = dfs(b, t, min(f, w))) > 0) {
                    w -= d;
                    g[b][i][1] += d;
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
            while ((d = dfs(s, t, inf)) > 0) {
                f += d;
            }
        }
        return f;
    }
};
