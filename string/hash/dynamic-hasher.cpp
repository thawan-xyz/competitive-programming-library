info combine(const info &a, const info &b) {
    info c;
    c.len = a.len + b.len;
    c.norm = (a.norm * b.pow + b.norm) % mod;
    c.rev = (b.rev * a.pow + a.rev) % mod;
    c.pow = a.pow * b.pow % mod;
    return c;
}

struct dynamic_hasher {
    int n;
    vector<info> tree;

    dynamic_hasher(const string &s): n(s.size()), tree(2 * n) {
        for (int i = 0; i < n; ++i) tree[n + i] = {1, s[i], s[i], base};
        for (int i = n - 1; i > 0; --i) tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
    }

    void update(int i, char c) {
        tree[i += n] = {1, c, c, base};
        for (i /= 2; i > 0; i /= 2) tree[i] = combine(tree[2 * i], tree[2 * i + 1]);
    }

    info query(int l, int r) {
        info a, b;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) a = combine(a, tree[l++]);
            if (r & 1) b = combine(tree[--r], b);
        }
        return combine(a, b);
    }
};
