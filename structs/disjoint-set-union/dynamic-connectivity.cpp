// Dynamic Connectivity: offline number of components at each time, with edges alive in time intervals
// Time: O(q + k log q log n) | Space: O(n + q + k log q), with k calls to insert
// Note: requires rb_dsu; insert(a, b, l, r) means edge (a, b) exists at times l..r of [0, q - 1]
struct dynamic_connectivity {
    int n, q;
    vector<vector<pair<int, int>>> tree;

    dynamic_connectivity(int n, int q): n(n), q(q), tree(4 * q) {}

    void insert(int a, int b, int ql, int qr) {
        auto rec = [&](auto &self, int p, int l, int r) -> void {
            if (qr < l or r < ql) return;
            if (ql <= l and r <= qr) return tree[p].push_back({a, b});
            int m = l + (r - l) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m + 1, r);
        };
        rec(rec, 1, 0, q - 1);
    }

    vector<int> compute() {
        rb_dsu d(n);
        vector<int> ans(q);
        auto rec = [&](auto &self, int p, int l, int r) -> void {
            int t = d.state();
            for (auto [a, b] : tree[p]) d.unite(a, b);
            if (l == r) {
                ans[l] = d.c;
            } else {
                int m = l + (r - l) / 2;
                self(self, 2 * p, l, m);
                self(self, 2 * p + 1, m + 1, r);
            }
            while (d.state() > t) d.rollback();
        };
        rec(rec, 1, 0, q - 1);
        return ans;
    }
};
