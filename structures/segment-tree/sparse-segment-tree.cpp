struct sparse_segment_tree {
private:
    struct node {
        int x = 0;
        int l = 0, r = 0;
    };

    int root = 0, min_l, max_r;
    vector<node> tree;

    int update(int i, int x, int p, int l, int r) {
        if (not p) {
            p = tree.size();
            tree.emplace_back();
        }
        if (l == r) {
            tree[p].x = x;
            return p;
        }
        int m = l + (r - l) / 2;
        if (i <= m) {
            int nl = update(i, x, tree[p].l, l, m);
            tree[p].l = nl;
        } else {
            int nr = update(i, x, tree[p].r, m + 1, r);
            tree[p].r = nr;
        }

        tree[p].x = tree[tree[p].l].x + tree[tree[p].r].x;
        return p;
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p or (qr < l or r < ql)) {
            return 0;
        }
        if (ql <= l and r <= qr) {
            return tree[p].x;
        }
        int m = l + (r - l) / 2;
        return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
    }

public:
    sparse_segment_tree(int l, int r, int q = 0): min_l(l), max_r(r) {
        tree.reserve(1 + 35 * q);
        tree.emplace_back();
    }

    void update(int i, int x) {
        root = update(i, x, root, min_l, max_r);
    }

    int query(int ql, int qr) {
        return query(ql, qr, root, min_l, max_r);
    }
};
