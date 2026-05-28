struct lazy_sparse_segment_tree {
private:
    struct node {
        int val = 0, lazy = 0;
        int l = 0, r = 0;
    };

    int root, min_l, max_r;
    vector<node> tree;

    void push(int p, int l, int r) {
        if (tree[p].lazy == 0) return;
        int m = l + (r - l) / 2;

        if (not tree[p].l) {
            tree[p].l = tree.size();
            tree.emplace_back();
        }
        if (not tree[p].r) {
            tree[p].r = tree.size();
            tree.emplace_back();
        }
    
        tree[tree[p].l].lazy += tree[p].lazy;
        tree[tree[p].r].lazy += tree[p].lazy;
        tree[tree[p].l].val += tree[p].lazy * (m - l + 1);
        tree[tree[p].r].val += tree[p].lazy * (r - m);
        tree[p].lazy = 0;
    }

    int update(int ql, int qr, int x, int p, int l, int r) {
        if (not p) p = tree.size(), tree.emplace_back();
        if (ql <= l and r <= qr) {
            tree[p].lazy += x;
            tree[p].val += x * (r - l + 1);
            return p;
        }
        push(p, l, r);

        int m = l + (r - l) / 2;
        if (ql <= m) tree[p].l = update(ql, qr, x, tree[p].l, l, m);
        if (qr > m) tree[p].r = update(ql, qr, x, tree[p].r, m + 1, r);

        tree[p].val = tree[tree[p].l].val + tree[tree[p].r].val;
        return p;
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p or (qr < l or r < ql)) return 0;
        if (ql <= l and r <= qr) return tree[p].val;
        push(p, l, r);

        int m = l + (r - l) / 2;
        return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
    }

public:
    lazy_sparse_segment_tree(int l, int r): root(0), min_l(l), max_r(r) {
        tree.reserve(2e5);
        tree.emplace_back();
    }

    void update(int ql, int qr, int x) {
        root = update(ql, qr, x, root, min_l, max_r);
    }

    int query(int ql, int qr) {
        return query(ql, qr, root, min_l, max_r);
    }
};
