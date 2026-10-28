struct binary_lifting {
    int n, log;
    vector<int> d;
    vector<vector<int>> up;

    binary_lifting(vector<vector<int>> &g) {
        n = g.size();
        log = __bit_width(n);
        d.assign(n, -1);
        up.assign(log, vector<int>(n));
        for (int s = 0; s < n; ++s) if (d[s] == -1) {
            d[s] = 0;
            up[0][s] = s;
            queue<int> q;
            q.push(s);
            while (q.size()) {
                int a = q.front(); q.pop();
                for (int b : g[a]) if (d[b] == -1) {
                    d[b] = d[a] + 1;
                    up[0][b] = a;
                    q.push(b);
                }
            }
        }
        for (int i = 1; i < log; ++i) {
            for (int a = 0; a < n; ++a) {
                up[i][a] = up[i - 1][up[i - 1][a]];
            }
        }
    }

    int kth(int a, int k) {
        k = min(k, d[a]);
        for (int i = 0; i < log; ++i) {
            if ((k >> i) & 1) a = up[i][a];
        }
        return a;
    }

    int lca(int a, int b) {
        if (d[a] < d[b]) swap(a, b);
        a = kth(a, d[a] - d[b]);
        if (a == b) return a;
        for (int i = log - 1; i >= 0; --i) {
            if (up[i][a] != up[i][b]) {
                a = up[i][a];
                b = up[i][b];
            }
        }
        return up[0][a];
    }

    int dist(int a, int b) {
        return d[a] + d[b] - 2 * d[lca(a, b)];
    }

    int path(int a, int b, int k) {
        int p = lca(a, b);
        int l = d[a] - d[p];
        int r = d[b] - d[p];
        k = min(k, l + r);
        if (k <= l) return kth(a, k);
        else return kth(b, l + r - k);
    }
};
