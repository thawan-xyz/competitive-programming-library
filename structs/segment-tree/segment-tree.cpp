struct segment_tree {
    struct node {
        int sum = 0, lazy = 0;
        int l = 0, r = 0;
    };

    void merge(node &c, const node &a, const node &b) {
        c.sum = a.sum + b.sum;
    }

    void apply(node &a, int x, int len) {
        a.sum += x * len;
        a.lazy += x;
    }

    int low, high, root = 0;
    bool persistent;
    vector<node> tree = {node()};

    segment_tree(int low, int high, bool persistent): low(low), high(high), persistent(persistent) {}

    int touch(int p) {
        if (p and not persistent) return p;
        tree.push_back(tree[p]);
        return tree.size() - 1;
    }

    void push(int p, int l, int r) {
        if (tree[p].lazy == tree[0].lazy) return;
        int m = l + (r - l) / 2;
        tree[p].l = touch(tree[p].l), tree[p].r = touch(tree[p].r);
        apply(tree[tree[p].l], tree[p].lazy, m - l + 1);
        apply(tree[tree[p].r], tree[p].lazy, r - m);
        tree[p].lazy = tree[0].lazy;
    }

    int set(int i, const node &x, int p = -1, int l = 1, int r = 0) {
        if (l > r) return root = set(i, x, p < 0 ? root : p, low, high);
        p = touch(p);
        if (l == r) return tree[p] = x, p;
        push(p, l, r);
        int m = l + (r - l) / 2;
        if (i <= m) tree[p].l = set(i, x, tree[p].l, l, m);
        else tree[p].r = set(i, x, tree[p].r, m + 1, r);
        merge(tree[p], tree[tree[p].l], tree[tree[p].r]);
        return p;
    }

    int update(int ql, int qr, int x, int p = -1, int l = 1, int r = 0) {
        if (l > r) return root = update(ql, qr, x, p < 0 ? root : p, low, high);
        if (qr < l or r < ql) return p;
        p = touch(p);
        if (ql <= l and r <= qr) return apply(tree[p], x, r - l + 1), p;
        push(p, l, r);
        int m = l + (r - l) / 2;
        tree[p].l = update(ql, qr, x, tree[p].l, l, m);
        tree[p].r = update(ql, qr, x, tree[p].r, m + 1, r);
        merge(tree[p], tree[tree[p].l], tree[tree[p].r]);
        return p;
    }

    node query(int ql, int qr, int p = -1, int l = 1, int r = 0) {
        if (l > r) return query(ql, qr, p < 0 ? root : p, low, high);
        if (qr < l or r < ql) return node();
        if (not p or (ql <= l and r <= qr)) return tree[p];
        push(p, l, r);
        int m = l + (r - l) / 2;
        node c;
        merge(c, query(ql, qr, tree[p].l, l, m), query(ql, qr, tree[p].r, m + 1, r));
        return c;
    }
};
