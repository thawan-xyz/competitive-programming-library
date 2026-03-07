struct hasher_segment_tree {
private:
    static constexpr array<int, 2> base = {41, 53};
    static constexpr array<int, 2> mod = {1000000007, 1000000009};

    struct node {
        int len = 0;
        array<int, 2> f_hash = {};
        array<int, 2> r_hash = {};
        
        node() = default;
        
        node(char c): len(1) {
            f_hash[0] = r_hash[0] = c % mod[0];
            f_hash[1] = r_hash[1] = c % mod[1];
        }
    };

    int n;
    vector<node> tree;
    vector<array<int, 2>> pow;

    node merge(const node &l, const node &r) {
        if (l.len == 0) return r;
        if (r.len == 0) return l;
        node m;
        m.len = l.len + r.len;
        m.f_hash[0] = (l.f_hash[0] * pow[r.len][0] + r.f_hash[0]) % mod[0];
        m.r_hash[0] = (r.r_hash[0] * pow[l.len][0] + l.r_hash[0]) % mod[0];
        m.f_hash[1] = (l.f_hash[1] * pow[r.len][1] + r.f_hash[1]) % mod[1];
        m.r_hash[1] = (r.r_hash[1] * pow[l.len][1] + l.r_hash[1]) % mod[1];
        return m;
    }

public:
    hasher_segment_tree(const string &s): n(s.length()), tree(2 * n), pow(n + 1) {
        pow[0][0] = pow[0][1] = 1;
        for (int i = 1; i <= n; ++i) {
            pow[i][0] = (pow[i - 1][0] * base[0]) % mod[0];
            pow[i][1] = (pow[i - 1][1] * base[1]) % mod[1];
        }

        for (int i = 0; i < n; ++i) tree[n + i] = node(s[i]);
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    void modify(int i, char c) {
        i += n;
        tree[i] = node(c);
        for (i >>= 1; i > 0; i >>= 1) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    node query(int i, int j) {
        node l, r;
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) l = merge(l, tree[i++]);
            if (j & 1) r = merge(tree[--j], r);
        }
        return merge(l, r);
    }

    bool palindrome(int i, int j) {
        if (i >= j) return true;
        node q = query(i, j);
        return q.f_hash == q.r_hash;
    }
};
