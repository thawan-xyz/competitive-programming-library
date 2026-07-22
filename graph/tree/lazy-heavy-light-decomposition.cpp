struct lazy_hld {
    int n;
    bool edge;
    vector<int> p, d, h, id;
    lazy_segment_tree s;

    lazy_hld(int r, vector<vector<int>> &g, bool edge): n(g.size()), edge(edge), p(n), d(n), h(n), id(n), s(n) {
        p[r] = r, d[r] = 0, dfs(r, g);
        h[r] = r, decompose(r, g, 0);
    }

    int dfs(int a, vector<vector<int>> &g) {
        int size = 1, max = 0;
        for (int &b : g[a]) if (b != p[a]) {
            p[b] = a, d[b] = d[a] + 1;
            int curr = dfs(b, g);
            if (curr > max) {
                max = curr;
                swap(g[a][0], b);
            }
            size += curr;
        }
        return size;
    }

    int decompose(int a, vector<vector<int>> &g, int i) {
        id[a] = i++;
        for (int b : g[a]) if (b != p[a]) {
            h[b] = (b == g[a][0]) ? h[a] : b;
            i = decompose(b, g, i);
        }
        return i;
    }

    int query(int a, int b) {
        int r = s.neutral;
        while (h[a] != h[b]) {
            if (d[h[a]] < d[h[b]]) swap(a, b);
            r = s.merge(r, s.query(id[h[a]], id[a]));
            a = p[h[a]];
        }
        if (d[a] > d[b]) swap(a, b);
        if (edge and a == b) return r;
        r = s.merge(r, s.query(id[a] + edge, id[b]));
        return r;
    }

    void update(int a, int b, int x) {
        while (h[a] != h[b]) {
            if (d[h[a]] < d[h[b]]) swap(a, b);
            s.update(id[h[a]], id[a], x);
            a = p[h[a]];
        }
        if (d[a] > d[b]) swap(a, b);
        if (edge and a == b) return;
        s.update(id[a] + edge, id[b], x);
    }
};
