// Segment Tree Beats: range add, chmin, chmax and mod, with range sum, max and min queries
// Time: query and add O(log N) | chmin and chmax amortized O(log^2 N) | mod amortized O(log N log C) | Space: O(N)
// Note: update(l, r, x, op): op '+' adds x, '<' sets a[i] = min(a[i], x), '>' max(a[i], x), '%' a[i] % x
struct segment_tree_beats {
    struct node {
        int sum = 0, lazy = 0;
        int max1 = -inf, max2 = -inf, maxc = 0;
        int min1 = inf, min2 = inf, minc = 0;
    };

    int n;
    vector<node> tree;

    node merge(const node &a, const node &b) {
        node c;
        c.sum = a.sum + b.sum;
        c.max1 = max(a.max1, b.max1);
        c.max2 = max(a.max1 == c.max1 ? a.max2 : a.max1, b.max1 == c.max1 ? b.max2 : b.max1);
        c.maxc = (a.max1 == c.max1 ? a.maxc : 0) + (b.max1 == c.max1 ? b.maxc : 0);
        c.min1 = min(a.min1, b.min1);
        c.min2 = min(a.min1 == c.min1 ? a.min2 : a.min1, b.min1 == c.min1 ? b.min2 : b.min1);
        c.minc = (a.min1 == c.min1 ? a.minc : 0) + (b.min1 == c.min1 ? b.minc : 0);
        return c;
    }

    void apply_add(node &a, int len, int x) {
        a.sum += x * len, a.lazy += x;
        a.max1 += x, a.min1 += x;
        if (a.max2 != -inf) a.max2 += x;
        if (a.min2 != inf) a.min2 += x;
    }

    void apply_min(node &a, int x) {
        if (x >= a.max1) return;
        a.sum -= (a.max1 - x) * a.maxc;
        if (a.min1 == a.max1) a.min1 = x;
        if (a.min2 == a.max1) a.min2 = x;
        a.max1 = x;
    }

    void apply_max(node &a, int x) {
        if (x <= a.min1) return;
        a.sum += (x - a.min1) * a.minc;
        if (a.max1 == a.min1) a.max1 = x;
        if (a.max2 == a.min1) a.max2 = x;
        a.min1 = x;
    }

    void push(int p, int l, int m, int r) {
        node &a = tree[p], &b = tree[2 * p], &c = tree[2 * p + 1];
        if (a.lazy != 0) {
            apply_add(b, m - l + 1, a.lazy);
            apply_add(c, r - m, a.lazy);
            a.lazy = 0;
        }
        apply_min(b, a.max1), apply_max(b, a.min1);
        apply_min(c, a.max1), apply_max(c, a.min1);
    }

    void build(const vector<int> &a, int p, int l, int r) {
        if (l == r) {
            tree[p].sum = tree[p].max1 = tree[p].min1 = a[l];
            tree[p].maxc = tree[p].minc = 1;
            return;
        }
        int m = (l + r) / 2;
        build(a, 2 * p, l, m);
        build(a, 2 * p + 1, m + 1, r);
        tree[p] = merge(tree[2 * p], tree[2 * p + 1]);
    }

    segment_tree_beats(const vector<int> &a): n(a.size()), tree(4 * n) {
        build(a, 1, 0, n - 1);
    }

    segment_tree_beats(int n): segment_tree_beats(vector<int>(n)) {}

    void update(int ql, int qr, int x, char op, int p = 1, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        node &a = tree[p];
        if (qr < l or r < ql) return;
        if ((op == '<' and x >= a.max1) or (op == '>' and x <= a.min1) or (op == '%' and a.max1 < x)) return;
        if (ql <= l and r <= qr) {
            if (op == '+') return apply_add(a, r - l + 1, x);
            if (op == '<' and x > a.max2) return apply_min(a, x);
            if (op == '>' and x < a.min2) return apply_max(a, x);
            if (op == '%' and a.min1 == a.max1) return apply_add(a, r - l + 1, a.max1 % x - a.max1);
        }
        int m = (l + r) / 2;
        push(p, l, m, r);
        update(ql, qr, x, op, 2 * p, l, m);
        update(ql, qr, x, op, 2 * p + 1, m + 1, r);
        a = merge(tree[2 * p], tree[2 * p + 1]);
    }

    node query(int ql, int qr, int p = 1, int l = 0, int r = -1) {
        if (r < 0) r = n - 1;
        if (qr < l or r < ql) return node();
        if (ql <= l and r <= qr) return tree[p];
        int m = (l + r) / 2;
        push(p, l, m, r);
        return merge(query(ql, qr, 2 * p, l, m), query(ql, qr, 2 * p + 1, m + 1, r));
    }
};
