struct binary_lifting {
    int n, log;
    vector<int> d;
    vector<vector<int>> up;

    void build(int a, int p, const vector<vector<int>> &g) {
        up[a][0] = p;
        for (int i = 1; i <= log; ++i) {
            up[a][i] = up[up[a][i - 1]][i - 1];
        }
        for (int b : g[a]) if (b != p) {
            d[b] = d[a] + 1;
            build(b, a, g);
        }
    }

    void init(const vector<vector<int>> &g) {
        n = g.size();
        log = __bit_width(n) - 1;
        d.assign(n, -1);
        up.assign(n, vector<int>(log + 1));
        for (int i = 0; i < n; ++i) if (d[i] == -1) {
            d[i] = 0;
            build(i, i, g);
        }
    }

    int kth(int a, int k) const {
        k = min(k, d[a]);
        while (k > 0) {
            int i = __bit_width(k) - 1;
            a = up[a][i];
            k ^= 1 << i;
        }
        return a;
    }

    int lca(int a, int b) const {
        if (d[a] < d[b]) swap(a, b);
        a = kth(a, d[a] - d[b]);
        if (a == b) return a;
        for (int i = log; i >= 0; --i) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }
        return up[a][0];
    }

    int dist(int a, int b) const {
        return d[a] + d[b] - 2 * d[lca(a, b)];
    }

    int path(int a, int b, int k) const {
        int p = lca(a, b);
        int l = d[a] - d[p];
        int r = d[b] - d[p];
        k = min(k, l + r);
        if (k <= l) return kth(a, k);
        else return kth(b, l + r - k);
    }
};
