struct hopcroft_karp {
    const int inf = 1e9;
    int n, m, s;
    vector<int> r, l, d;
    vector<vector<int>> g;

    hopcroft_karp(int n, int m): n(n), m(m), r(n, -1), l(m, -1), d(n), g(n) {}

    void edge(int a, int b) {
        g[a].push_back(b);
    }

    bool bfs() {
        s = inf;
        queue<int> q;
        for (int a = 0; a < n; ++a) {
            if (r[a] == -1) {
                d[a] = 0;
                q.push(a);
            } else {
                d[a] = inf;
            }
        }
        while (q.size()) {
            int a = q.front(); q.pop();
            if (d[a] >= s) continue;
            for (int b : g[a]) {
                if (l[b] == -1) {
                    s = min(s, d[a] + 1);
                } else if (d[l[b]] == inf) {
                    d[l[b]] = d[a] + 1;
                    q.push(l[b]);
                }
            }
        }
        return s != inf;
    }

    bool dfs(int a) {
        if (a == -1) return true;
        for (int b : g[a]) {
            int h = (l[b] != -1) ? d[l[b]] : s;
            if (h == d[a] + 1) if (dfs(l[b])) {
                r[a] = b;
                l[b] = a;
                return true;
            }
        }
        d[a] = inf;
        return false;
    }

    int match() {
        int matching = 0;
        while (bfs()) {
            for (int a = 0; a < n; ++a) if (r[a] == -1 and dfs(a)) matching++;
        }
        return matching;
    }

    vector<pair<int, int>> matches() {
        vector<pair<int, int>> m;
        for (int a = 0; a < n; ++a) if (r[a] != -1) m.emplace_back(a, r[a]);
        return m;
    }
};
