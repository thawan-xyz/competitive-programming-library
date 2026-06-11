struct sparse_persistent_segment_tree {
private:
    struct node {
        int x = 0;
        int l = 0, r = 0;
    };

    int min_l, max_r;
    vector<node> tree;

    int clone(int p) {
        tree.push_back(tree[p]);
        return tree.size() - 1;
    }

    int update(int i, int x, int p, int l, int r) {
        int c = clone(p);
        if (l == r) {
            tree[c].x += x;
            return c;
        }
        int m = l + (r - l) / 2;
        if (i <= m) {
            int nl = update(i, x, tree[c].l, l, m);
            tree[c].l = nl;
        } else {
            int nr = update(i, x, tree[c].r, m + 1, r);
            tree[c].r = nr;
        }
        tree[c].x = tree[tree[c].l].x + tree[tree[c].r].x;
        return c;
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p or qr < l or r < ql) return 0;
        if (ql <= l and r <= qr) return tree[p].x;
        int m = l + (r - l) / 2;
        return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
    }

public:
    vector<int> roots;

    sparse_persistent_segment_tree(int l, int r, int q = 0): min_l(l), max_r(r) {
        tree.reserve(1 + 35 * q);
        tree.emplace_back();
        roots.push_back(0);
    }

    void update(int i, int x, int v = -1) {
        if (v == -1) v = roots.size() - 1;
        roots.push_back(update(i, x, roots[v], min_l, max_r));
    }

    int query(int ql, int qr, int v = -1) {
        if (v == -1) v = roots.size() - 1;
        return query(ql, qr, roots[v], min_l, max_r);
    }
};
