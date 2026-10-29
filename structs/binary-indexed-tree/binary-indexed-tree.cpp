struct bit {
    int n;
    vector<int> tree;

    static int lsb(int i) {
        return i & -i;
    }

    bit(int n = 0): n(n), tree(n + 1) {}

    void update(int i, int x) {
        for (i += 1; i <= n; i += lsb(i)) tree[i] += x;
    }

    int prefix(int i) {
        int s = 0;
        for (i += 1; i > 0; i -= lsb(i)) s += tree[i];
        return s;
    }

    int query(int i, int j) {
        return prefix(j) - prefix(i - 1);
    }

    int find_kth(int k) {
        assert(k >= 0);
        k += 1;
        int i = 0;
        for (int s = 1 << __lg(n); s > 0; s >>= 1) if (i + s <= n and tree[i + s] < k) {
            i += s;
            k -= tree[i];
        }
        return i;
    }
};

struct bit_2d {
    int n, m;
    vector<bit> tree;

    bit_2d(int n = 0, int m = 0): n(n), m(m), tree(n + 1, bit(m)) {}

    void build(vector<vector<int>> &a) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                update(i, j, a[i][j]);
            }
        }
    }

    void update(int i, int j, int x) {
        for (i += 1; i <= n; i += i & -i) tree[i].update(j, x);
    }

    int prefix(int i, int j) {
        int s = 0;
        for (i += 1; i > 0; i -= i & -i) s += tree[i].prefix(j);
        return s;
    }

    int query(int i, int j, int p, int q) {
        return prefix(p, q)
             - prefix(i - 1, q)
             - prefix(p, j - 1)
             + prefix(i - 1, j - 1);
    }
};
