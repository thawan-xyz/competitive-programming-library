block init(char c) {
    block h;
    h.len = 1;
    for (int i = 0; i <= 1; ++i) {
        h.ord[i] = c % mod[i];
        h.rev[i] = c % mod[i];
    }
    return h;
}

block combine(const block &l, const block &r) {
    if (l.len == 0) return r;
    if (r.len == 0) return l;
    extend(max(l.len, r.len));
    block m;
    m.len = l.len + r.len;
    for (int i = 0; i <= 1; ++i) {
        m.ord[i] = (l.ord[i] * pows[r.len][i] + r.ord[i]) % mod[i];
        m.rev[i] = (r.rev[i] * pows[l.len][i] + l.rev[i]) % mod[i];
    }
    return m;
}

struct dynamic_hasher {
    int n;
    vector<block> tree;

    dynamic_hasher(const string &s): n(s.length()), tree(2 * n) {
        for (int i = 0; i < n; ++i) tree[n + i] = init(s[i]);
        for (int i = n - 1; i > 0; --i) tree[i] = combine(tree[i << 1], tree[(i << 1) | 1]);
    }

    void update(int i, char c) {
        tree[i += n] = init(c);
        for (i >>= 1; i > 0; i >>= 1) tree[i] = combine(tree[i << 1], tree[(i << 1) | 1]);
    }

    block query(int i, int j) {
        block l, r;
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) l = combine(l, tree[i++]);
            if (j & 1) r = combine(tree[--j], r);
        }
        return combine(l, r);
    }
};
