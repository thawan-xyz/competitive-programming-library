struct dynamic_connectivity {
private:
    int n, q;
    vector<vector<pair<int, int>>> tree;
    rollback_dsu dsu;

    void insert(pair<int, int> e, int ql, int qr, int p, int l, int r) {
        if (qr < l or ql > r) return;
        if (ql <= l and qr >= r) return void(tree[p].push_back(e));
        int m = (l + r) / 2;
        insert(e, ql, qr, 2 * p, l, m);
        insert(e, ql, qr, 2 * p + 1, m + 1, r);
    }

    void compute(vector<int> &ans, int p, int l, int r) {
        for (auto [a, b] : tree[p]) dsu.unite(a, b);
        if (l == r) {
            ans[l] = dsu.c;
        } else {
            int m = (l + r) / 2;
            compute(ans, 2 * p, l, m);
            compute(ans, 2 * p + 1, m + 1, r);
        }
        for (auto [a, b] : tree[p]) dsu.rollback();
    }

public:
    dynamic_connectivity(int n, int q): n(n), q(q), tree(4 * q), dsu(n) {}

    void insert(pair<int, int> e, int ql, int qr) {
        insert(e, ql, qr, 1, 0, q - 1);
    }

    vector<int> compute() {
        vector<int> ans(q);
        compute(ans, 1, 0, q - 1);
        return ans;
    }
};
