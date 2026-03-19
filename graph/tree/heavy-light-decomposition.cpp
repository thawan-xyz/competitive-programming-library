struct hld {
    int n;
    vector<int> p, d, h, sz, id;
    reversable_segment_tree s, t;

    hld(int r, vector<vector<int>> &g): n(g.sz()), p(n), d(n), h(n), sz(n), id(n), s(n, false), t(n, true) {
        d[r] = 0, dfs(r, g);
        h[r] = r, decompose(r, g, 0);
    }

    void dfs(int a, vector<vector<int>> &g) {
        sz[a] = 1;
        for (int &b : g[a]) if (b != p[a]) {
            p[b] = a, d[b] = d[a] + 1;
            dfs(b, g), sz[a] += sz[b];
            if (g[a][0] == p[a] or sz[b] > sz[g[a][0]]) {
                swap(g[a][0], b);
            }
        }
    }

    int decompose(int a, vector<vector<int>> &g, int timer) {
        id[a] = timer++;
        for (int b : g[a]) if (b != p[a]) {
            h[b] = (b == g[a][0]) ? h[a] : b;
            timer = decompose(b, g, timer);
        }
        return timer;
    }

    int query(int a, int b) {
        int l = s.neutral, r = s.neutral;
        while (h[a] != h[b]) {
            if (d[h[a]] > d[h[b]]) {
                l = s.merge(l, t.query(id[h[a]], id[a]));
                a = p[h[a]];
            } else {
                r = s.merge(s.query(id[h[b]], id[b]), r);
                b = p[h[b]];
            }
        }
        if (d[a] > d[b]) l = s.merge(l, t.query(id[b], id[a]));
        else r = s.merge(s.query(id[a], id[b]), r);
        return s.merge(l, r);
    }

    void update(int a, int x) {
        s.update(id[a], x);
        t.update(id[a], x);
    }
};
