struct heavy_light_decomposition {
    int n, timer = 0;
    list<list<int>> &g;
    list<int> p, d, h;
    segment_tree s;
    list<int> size, id;

    heavy_light_decomposition(list<list<int>> &g, int root = 1): n(g.size()), g(g), p(n), d(n), h(n), s(n), size(n), id(n) {
        d[root] = 1;
        dfs(root);
        h[root] = root;
        decompose(root);
    }

    void dfs(int a) {
        size[a] = 1;
        for (int &b : g[a]) if (b != p[a]) {
            p[b] = a;
            d[b] = d[a] + 1;
            dfs(b);
            size[a] += size[b];
            if (g[a][0] == p[a] or size[b] > size[g[a][0]]) {
                swap(g[a][0], b);
            }
        }
    }

    void decompose(int a) {
        id[a] = ++timer;
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
        int l = s.neutral;
        int r = s.neutral;
        while (h[a] != h[b]) {
            if (d[h[a]] > d[h[b]]) {
                l = s.combine(l, s.query(id[h[a]], id[a]));
                a = p[h[a]];
            } else {
                r = s.combine(s.query_reverse(id[h[b]], id[b]), r);
                b = p[h[b]];
            }
        }
        if (d[a] > d[b]) {
            l = s.combine(l, s.query(id[b], id[a]));
        } else {
            r = s.combine(s.query_reverse(id[a], id[b]), r);
        }
        return s.combine(l, r);
    }

    void modify(int a, int x) {
        s.modify(id[a], x);
    }
};
