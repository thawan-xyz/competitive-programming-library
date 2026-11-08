struct segment_tree {
    struct tag {
        int x = 0;

        bool operator==(const tag &o) const {
            return x == o.x;
        }
    };

    struct node {
        int sum = 0;
        tag lazy;
    };

    node merge(const node &a, const node &b) {
        node c;
        c.sum = a.sum + b.sum;
        return c;
    }

    void apply(node &a, int len, const tag &t) {
        a.sum += t.x * len;
        a.lazy.x += t.x;
    }

    bool good(const node &a, int x) {
        return a.sum >= x;
    }

    int n;
    vector<node> tree;
    node acc;

    segment_tree(int n): n(n), tree(4 * n) {}

    void push(int p, int l, int r) {
        if (tree[p].lazy == tag()) return;
        int m = l + (r - l) / 2;
        apply(tree[2 * p], m - l + 1, tree[p].lazy);
        apply(tree[2 * p + 1], r - m, tree[p].lazy);
        tree[p].lazy = tag();
    }

    void pull(int p) {
        tree[p] = merge(tree[2 * p], tree[2 * p + 1]);
    }

    void build(const vector<node> &a, int p = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (l == r) {
            tree[p] = a[l];
            return;
        }
        int m = l + (r - l) / 2;
        build(a, 2 * p, l, m);
        build(a, 2 * p + 1, m + 1, r);
        pull(p);
    }

    void set(int i, const node &x, int p = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (l == r) {
            tree[p] = x;
            return;
        }
        push(p, l, r);
        int m = l + (r - l) / 2;
        if (i <= m) set(i, x, 2 * p, l, m);
        else set(i, x, 2 * p + 1, m + 1, r);
        pull(p);
    }

    void update(int ql, int qr, const tag &t, int p = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (qr < l or r < ql) return;
        if (ql <= l and r <= qr) return apply(tree[p], r - l + 1, t);
        push(p, l, r);
        int m = l + (r - l) / 2;
        update(ql, qr, t, 2 * p, l, m);
        update(ql, qr, t, 2 * p + 1, m + 1, r);
        pull(p);
    }

    node query(int ql, int qr, int p = 1, int l = 0, int r = -1) {
        if (r == -1) r = n - 1;
        if (qr < l or r < ql) return node();
        if (ql <= l and r <= qr) return tree[p];
        push(p, l, r);
        int m = l + (r - l) / 2;
        return merge(query(ql, qr, 2 * p, l, m), query(ql, qr, 2 * p + 1, m + 1, r));
    }

    int left(int qr, int x, int p = 1, int l = 0, int r = -1) {
        if (r == -1) acc = node(), r = n - 1;
        if (qr < l) return l - 1;
        node c = merge(tree[p], acc);
        if (r <= qr and not good(c, x)) return acc = c, l - 1;
        if (l == r) return l;
        push(p, l, r);
        int m = l + (r - l) / 2, i = left(qr, x, 2 * p + 1, m + 1, r);
        return i > m ? i : left(qr, x, 2 * p, l, m);
    }

    int right(int ql, int x, int p = 1, int l = 0, int r = -1) {
        if (r == -1) acc = node(), r = n - 1;
        if (r < ql) return r + 1;
        node c = merge(acc, tree[p]);
        if (ql <= l and not good(c, x)) return acc = c, r + 1;
        if (l == r) return l;
        push(p, l, r);
        int m = l + (r - l) / 2, i = right(ql, x, 2 * p, l, m);
        return i <= m ? i : right(ql, x, 2 * p + 1, m + 1, r);
    }
};
