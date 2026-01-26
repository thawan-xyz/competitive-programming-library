struct sparse_segment_tree {
private:
    struct node {
        int x, l, r;

        node(int x = 0, int l = 0, int r = 0): x(x), l(l), r(r) {}
    };

    int n, root;
    list<node> tree;

    int update(int i, int x, int p, int l, int r) {
        if (i > r or i < l) return p;

        if (not p) {
            p = tree.size();
            tree.push_back(node());
        }

        if (l == r) {
            tree[p].x += x;
            return p;
        }

        int m = (l + r) / 2;
        tree[p].l = update(i, x, tree[p].l, l, m);
        tree[p].r = update(i, x, tree[p].r, m + 1, r);
        tree[p].x = tree[tree[p].l].x + tree[tree[p].r].x;
        return p;
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p or (ql > r or qr < l)) return 0;

        if (ql <= l and qr >= r) return tree[p].x;

        int m = (l + r) / 2;
        return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
    }

public:
    sparse_segment_tree(int n): n(n), root(0), tree(1) {
        tree.reserve(2 * n);
    }

    void update(int i, int x) {
        root = update(i, x, root, 0, n - 1);
    }

    int query(int l, int r) {
        return query(l, r, root, 0, n - 1);
    }
};
