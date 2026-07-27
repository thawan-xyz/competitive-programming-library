struct reversible_hld {
    int n;
    bool e;
    reversible_segment_tree s, t;
    vector<int> p, d, h, id;

    reversible_hld(vector<vector<int>> &g, bool e): n(g.size()), e(e), s(n, false), t(n, true) {
        p.assign(n, -1);
        d.assign(n, 0);
        h.assign(n, 0);
        id.assign(n, 0);
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (p[i] == -1) {
                p[i] = i;
                d[i] = 0;
                dfs(i, g);
                h[i] = i;
                decompose(i, k, g);
            }
        }
    }

    int dfs(int a, vector<vector<int>> &g) {
        int size = 1, max = 0;
        for (int &b : g[a]) if (b != p[a]) {
            p[b] = a;
            d[b] = d[a] + 1;
            int curr = dfs(b, g);
            if (curr > max) {
                max = curr;
                swap(g[a][0], b);
            }
            size += curr;
        }
        return size;
    }

    void decompose(int a, int &k, vector<vector<int>> &g) {
        id[a] = k++;
        for (int b : g[a]) if (b != p[a]) {
            h[b] = b;
            if (b == g[a][0]) h[b] = h[a];
            decompose(b, k, g);
        }
    }

    int lca(int a, int b) {
        while (h[a] != h[b]) {
            if (d[h[a]] < d[h[b]]) swap(a, b);
            a = p[h[a]];
        }
        if (d[a] > d[b]) swap(a, b);
        return a;
    }

    int query(int a, int b) {
        int l = s.neutral;
        int r = s.neutral;
        while (h[a] != h[b]) {
            if (d[h[a]] > d[h[b]]) {
                l = t.merge(l, t.query(id[h[a]], id[a]));
                a = p[h[a]];
            } else {
                r = s.merge(s.query(id[h[b]], id[b]), r);
                b = p[h[b]];
            }
        }
        if (e and a == b) return s.merge(l, r);
        if (d[a] > d[b]) {
            l = t.merge(l, t.query(id[b] + e, id[a]));
        } else {
            r = s.merge(s.query(id[a] + e, id[b]), r);
        }
        return s.merge(l, r);
    }

    void update(int a, int x) {
        s.update(id[a], x);
        t.update(id[a], x);
    }
};
