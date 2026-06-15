struct dynamic_connectivity {
private:
    int n, q;
    vector<vector<pair<int, int>>> tree;
    rollback_dsu dsu;
    vector<int> ans;

    void insert(int i, int l, int r, int ql, int qr, pair<int, int> e) {
        if (qr < l or ql > r) return;
        if (ql <= l and qr >= r) return void(tree[i].push_back(e));
        int m = (l + r) / 2;
        insert(2 * i, l, m, ql, qr, e);
        insert(2 * i + 1, m + 1, r, ql, qr, e);
    }

    void compute(int i, int l, int r) {
        for (auto [a, b] : tree[i]) dsu.unite(a, b);
        if (l == r) {
            ans[l] = dsu.c;
        } else {
            int m = (l + r) / 2;
            compute(2 * i, l, m);
            compute(2 * i + 1, m + 1, r);
        }
        for (int k = 0; k < tree[i].size(); ++k) dsu.rollback();
    }

public:
    dynamic_connectivity(int n, int q): n(n), q(q), tree(4 * q), dsu(n), ans(q) {}

    void insert(int ql, int qr, pair<int, int> e) {
        insert(1, 0, q - 1, ql, qr, e);
    }

    vector<int> compute() {
        compute(1, 0, q - 1);
        return ans;
    }
};
