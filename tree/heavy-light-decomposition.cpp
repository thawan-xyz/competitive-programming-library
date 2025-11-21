struct heavy_light_decomposition {
    int n, t;
    array<array<int>> &g;
    array<int> p, s, d, h, l;
    segment_tree q;

    heavy_light_decomposition(array<array<int>> &g, int r = 1): n(g.size() - 1), t(0), g(g), p(n + 1), s(n + 1), d(n + 1), h(n + 1), l(n + 1), q(n + 1) {
        d[r] = 1;
        dfs(r);
        h[r] = r;
        decompose(r);
    }

    void dfs(int a) {
        s[a] = 1;
        for (int &b : g[a]) if (b != p[a]) {
            p[b] = a;
            d[b] = d[a] + 1;
            dfs(b);
            s[a] += s[b];
            if (g[a][0] == p[a] or s[b] > s[g[a][0]]) {
                swap(g[a][0], b);
            }
        }
    }

    void decompose(int a) {
        l[a] = ++t;
        for (int b : g[a]) if (b != p[a]) {
            if (b == g[a][0]) {
                h[b] = h[a];
            } else {
                h[b] = b;
            }
            decompose(b);
        }
    }

    int query(int a, int b) {
        int r = q.neutral;
        while (h[a] != h[b]) {
            if (d[h[a]] < d[h[b]]) swap(a, b);
            r = q.combine(r, q.query(l[h[a]], l[a]));
            a = p[h[a]];
        }
        if (d[a] > d[b]) swap(a, b);
        r = q.combine(r, q.query(l[a], l[b]));
        return r;
    }
};
