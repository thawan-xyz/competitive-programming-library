struct binary_lifting {
    int n, log;
    vector<int> d;
    vector<vector<int>> up;

    binary_lifting(int r, vector<vector<int>> &g): n(g.size()), log(31 - __builtin_clz(n)), d(n), up(n, vector<int>(log + 1)) {
        d[r] = 0;
        build(r, r, g);
    }

    void build(int a, int p, vector<vector<int>> &g) {
        up[a][0] = p;
        for (int i = 1; i <= log; ++i) {
            up[a][i] = up[up[a][i - 1]][i - 1];
        }

        for (int b : g[a]) if (b != p) {
            d[b] = d[a] + 1;
            build(b, a, g);
        }
    }

    int kth_ancestor(int a, int k) {
        if (d[a] < k) return -1;

        for (int i = log; i >= 0; --i) {
            if (k & (1 << i)) {
                a = up[a][i];
            }
        }
        return a;
    }

    int lowest_common_ancestor(int a, int b) {
        if (d[a] < d[b]) swap(a, b);
        a = kth_ancestor(a, d[a] - d[b]);
        if (a == b) return a;

        for (int i = log; i >= 0; --i) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }
        return up[a][0];
    }

    int kth_node(int a, int b, int k) {
        int lca = lowest_common_ancestor(a, b);
        int l = d[a] - d[lca];
        int r = d[b] - d[lca];
        if (k > l + r) return -1;

        if (k <= l) return kth_ancestor(a, k);
        return kth_ancestor(b, r - (k - l));
    }
};
