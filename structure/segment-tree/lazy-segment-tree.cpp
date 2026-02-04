struct lazy_segment_tree {
private:
    struct node {
        int x, y, l, r;

        node(): x(0), y(0), l(0), r(0) {}
    };

    int n, root;
    list<node> tree;

    int build(list<int> &a, int l, int r) {
        int p = tree.size();
        tree.push_back(node());
        if (l == r) {
            tree[p].x = a[l];
        } else {
            int m = (l + r) / 2;
            tree[p].l = build(a, l, m);
            tree[p].r = build(a, m + 1, r);
            tree[p].x = tree[tree[p].l].x + tree[tree[p].r].x;
        }
        return p;
    }

    void push(int p, int l, int r) {
        if (tree[p].y == 0) return;

        tree[p].x += (r - l + 1) * tree[p].y;
        if (l != r) {
            tree[tree[p].l].y += tree[p].y;
            tree[tree[p].r].y += tree[p].y;
        }
        tree[p].y = 0;
    }

    void modify(int ql, int qr, int x, int p, int l, int r) {
        if (ql > r or qr < l) return;
        push(p, l, r);

        if (ql <= l and qr >= r) {
            tree[p].y += x;
            push(p, l, r);
        } else {
            int m = (l + r) / 2;
            modify(ql, qr, x, tree[p].l, l, m);
            modify(ql, qr, x, tree[p].r, m + 1, r);
            tree[p].x = tree[tree[p].l].x + tree[tree[p].r].x;
        }
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (ql > r or qr < l) return 0;
        push(p, l, r);

        if (ql <= l and qr >= r) {
            return tree[p].x;
        } else {
            int m = (l + r) / 2;
            return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
        }
    }

public:
    lazy_segment_tree(int n): n(n), tree(1) {
        tree.reserve(2 * n);
    }

    void build(list<int> &a) {
        root = build(a, 0, n - 1);
    }

    void modify(int l, int r, int x) {
        modify(l, r, x, root, 0, n - 1);
    }

    int query(int l, int r) {
        return query(l, r, root, 0, n - 1);
    }
};
