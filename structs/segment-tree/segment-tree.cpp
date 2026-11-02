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
        int l = 0, r = 0;
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

    int low, high, root = 0;
    bool keep;
    vector<node> tree = {node()};
    node acc;

    segment_tree(int low, int high, bool keep): low(low), high(high), keep(keep) {}

    int touch(int p) {
        if (p and not keep) return p;
        tree.push_back(tree[p]);
        return tree.size() - 1;
    }

    void push(int p, int l, int r) {
        if (tree[p].lazy == tree[0].lazy) return;
        int m = l + (r - l) / 2;
        tree[p].l = touch(tree[p].l), tree[p].r = touch(tree[p].r);
        tag t = tree[p].lazy;
        apply(tree[tree[p].l], m - l + 1, t);
        apply(tree[tree[p].r], r - m, t);
        tree[p].lazy = tree[0].lazy;
    }

    void pull(int p) {
        node c = merge(tree[tree[p].l], tree[tree[p].r]);
        c.l = tree[p].l, c.r = tree[p].r;
        tree[p] = c;
    }

    int set(int i, const node &x, int p = -1, int l = 1, int r = 0) {
        if (l > r) return root = set(i, x, p < 0 ? root : p, low, high);
        p = touch(p);
        if (l == r) return tree[p] = x, p;
        push(p, l, r);
        int m = l + (r - l) / 2;
        if (i <= m) tree[p].l = set(i, x, tree[p].l, l, m);
        else tree[p].r = set(i, x, tree[p].r, m + 1, r);
        pull(p);
        return p;
    }

    int update(int ql, int qr, const tag &t, int p = -1, int l = 1, int r = 0) {
        if (l > r) return root = update(ql, qr, t, p < 0 ? root : p, low, high);
        if (qr < l or r < ql) return p;
        p = touch(p);
        if (ql <= l and r <= qr) return apply(tree[p], r - l + 1, t), p;
        push(p, l, r);
        int m = l + (r - l) / 2;
        tree[p].l = update(ql, qr, t, tree[p].l, l, m);
        tree[p].r = update(ql, qr, t, tree[p].r, m + 1, r);
        pull(p);
        return p;
    }

    node query(int ql, int qr, int p = -1, int l = 1, int r = 0) {
        if (l > r) return query(ql, qr, p < 0 ? root : p, low, high);
        if (qr < l or r < ql) return node();
        if (not p or (ql <= l and r <= qr)) return tree[p];
        push(p, l, r);
        int m = l + (r - l) / 2;
        return merge(query(ql, qr, tree[p].l, l, m), query(ql, qr, tree[p].r, m + 1, r));
    }

    int left(int qr, int x, int p = -1, int l = 1, int r = 0) {
        if (l > r) return acc = node(), left(qr, x, p < 0 ? root : p, low, high);
        if (qr < l) return l - 1;
        node c = merge(tree[p], acc);
        if (r <= qr and not good(c, x)) return acc = c, l - 1;
        if (l == r) return l;
        push(p, l, r);
        int m = l + (r - l) / 2, i = left(qr, x, tree[p].r, m + 1, r);
        return i > m ? i : left(qr, x, tree[p].l, l, m);
    }

    int right(int ql, int x, int p = -1, int l = 1, int r = 0) {
        if (l > r) return acc = node(), right(ql, x, p < 0 ? root : p, low, high);
        if (r < ql) return r + 1;
        node c = merge(acc, tree[p]);
        if (ql <= l and not good(c, x)) return acc = c, r + 1;
        if (l == r) return l;
        push(p, l, r);
        int m = l + (r - l) / 2, i = right(ql, x, tree[p].l, l, m);
        return i <= m ? i : right(ql, x, tree[p].r, m + 1, r);
    }
};
