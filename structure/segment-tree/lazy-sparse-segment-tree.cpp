struct lazy_sparse_segment_tree {
private:
    struct node {
        int x, y, l, r;

        node(int x = 0, int y = 0, int l = 0, int r = 0): x(x), y(y), l(l), r(r) {}
    };

    int n, root;
    list<node> tree;

    int merge(int x, int y) {
        return x + y;
    }

    void update(int p, int x, int l) {
        tree[p].x += x * l;
        tree[p].y += x;
    }

    void push(int p, int l, int r) {
        if (not p or tree[p].y == 0) return;

        if (not tree[p].l) {
            tree[p].l = tree.size();
            tree.push_back(node());
        }
        if (not tree[p].r) {
            tree[p].r = tree.size();
            tree.push_back(node());
        }

        int m = (l + r) / 2;
        update(tree[p].l, tree[p].y, (m - l) + 1);
        update(tree[p].r, tree[p].y, r - m);

        tree[p].y = 0;
    }

    int modify(int ql, int qr, int x, int p, int l, int r) {
        if (ql > r or qr < l) return p;

        if (not p) {
            p = tree.size();
            tree.push_back(node());
        }

        if (ql <= l and qr >= r) {
            update(p, x, (r - l) + 1);
            return p;
        }

        push(p, l, r);

        int m = (l + r) / 2;
        tree[p].l = modify(ql, qr, x, tree[p].l, l, m);
        tree[p].r = modify(ql, qr, x, tree[p].r, m + 1, r);
        tree[p].x = merge(tree[tree[p].l].x, tree[tree[p].r].x);
        return p;
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p or (ql > r or qr < l)) return 0;

        if (ql <= l and qr >= r) return tree[p].x;

        push(p, l, r);

        int m = (l + r) / 2;
        return merge(query(ql, qr, tree[p].l, l, m), query(ql, qr, tree[p].r, m + 1, r));
    }

public:
    lazy_sparse_segment_tree(int n): n(n), root(0), tree(1) {
        tree.reserve(2e5);
    }

    void modify(int l, int r, int x) {
        root = modify(l, r, x, root, 0, n - 1);
    }

    int query(int l, int r) {
        return query(l, r, root, 0, n - 1);
    }
};
