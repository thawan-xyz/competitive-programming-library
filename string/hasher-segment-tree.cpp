const array<int, 2> base = {41, 53};
const array<int, 2> mod = {1000000007, 1000000009};

struct hasher_segment_tree {
    struct node {
        int len = 0;
        array<int, 2> normal = {};
        array<int, 2> reverse = {};
        
        node() = default;
        
        node(char c) {
            len = 1;
            for (int i : {0, 1}) normal[i] = reverse[i] = c % mod[i];
        }
    };

    int n;
    vector<node> tree;
    vector<array<int, 2>> pow;

    node merge(const node &l, const node &r) {
        node m;
        m.len = l.len + r.len;
        for (int i : {0, 1}) {
            m.normal[i] = (l.normal[i] * pow[r.len][i] + r.normal[i]) % mod[i];
            m.reverse[i] = (r.reverse[i] * pow[l.len][i] + l.reverse[i]) % mod[i];
        }
        return m;
    }

    hasher_segment_tree(const string &s): n(s.length()), tree(2 * n), pow(n + 1) {
        pow[0] = {1, 1};
        for (int i = 0; i < n; ++i) {
            for (int j : {0, 1}) pow[i + 1][j] = (pow[i][j] * base[j]) % mod[j];
            tree[n + i] = node(s[i]);
        }
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[(i << 1) | 1]);
    }

    void update(int i, char c) {
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
};
