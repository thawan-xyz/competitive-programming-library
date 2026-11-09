struct bit_2d {
    int n, m;
    vector<bit> tree;

    int lsb(int i) {
        return i & -i;
    }

    bit_2d(int n = 0, int m = 0): n(n), m(m), tree(n + 1, bit(m)) {}

    bit_2d(const vector<vector<int>> &a): bit_2d(a.size(), a[0].size()) {
        for (int i = 1; i <= n; ++i) {
            bit row(a[i - 1]);
            for (int j = 1; j <= m; ++j) {
                tree[i].tree[j] += row.tree[j];
                if (i + lsb(i) <= n) tree[i + lsb(i)].tree[j] += tree[i].tree[j];
            }
        }
    }

    void update(int r, int c, int x) {
        for (r += 1; r <= n; r += lsb(r)) tree[r].update(c, x);
    }

    int prefix(int r, int c) {
        int s = 0;
        for (r += 1; r > 0; r -= lsb(r)) s += tree[r].prefix(c);
        return s;
    }

    int query(int r1, int c1, int r2, int c2) {
        return prefix(r2, c2) - prefix(r1 - 1, c2) - prefix(r2, c1 - 1) + prefix(r1 - 1, c1 - 1);
    }
};
