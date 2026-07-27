struct lazy_hld {
    int n;
    bool e;
    lazy_segment_tree s;
    vector<int> p, d, h, id;

    lazy_hld(vector<vector<int>> &g, bool e): n(g.size()), e(e), s(n) {
        p.assign(n, -1);
        d.assign(n, 0);
        h.assign(n, 0);
        id.assign(n, 0);
        int t = 0;
        for (int i = 0; i < n; ++i) {
            if (p[i] == -1) {
                p[i] = i;
                d[i] = 0;
                dfs(i, g);
                h[i] = i;
                decompose(i, t, g);
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

    void decompose(int a, int &t, vector<vector<int>> &g) {
        id[a] = t++;
        for (int b : g[a]) if (b != p[a]) {
            h[b] = b;
            if (b == g[a][0]) h[b] = h[a];
            decompose(b, t, g);
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
        int r = s.neutral;
        while (h[a] != h[b]) {
            if (d[h[a]] < d[h[b]]) swap(a, b);
            r = s.merge(r, s.query(id[h[a]], id[a]));
            a = p[h[a]];
        }
        if (d[a] > d[b]) swap(a, b);
        if (e and a == b) return r;
        r = s.merge(r, s.query(id[a] + e, id[b]));
        return r;
    }

    void update(int a, int b, int x) {
        while (h[a] != h[b]) {
            if (d[h[a]] < d[h[b]]) swap(a, b);
            s.update(id[h[a]], id[a], x);
            a = p[h[a]];
        }
        if (d[a] > d[b]) swap(a, b);
        if (e and a == b) return;
        s.update(id[a] + e, id[b], x);
    }
};
