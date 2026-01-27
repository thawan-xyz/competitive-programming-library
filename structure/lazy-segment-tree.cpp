struct lazy_segment_tree {
private:
    struct node {
        int x, l, r, lazy;

        node(int x = 0, int l = 0, int r = 0, int lazy = 0): x(x), l(l), r(r), lazy(lazy) {}
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
        if (tree[p].lazy == 0) return;

        tree[p].x += (r - l + 1) * tree[p].lazy;
        if (l != r) {
            tree[tree[p].l].lazy += tree[p].lazy;
            tree[tree[p].r].lazy += tree[p].lazy;
        }
        tree[p].lazy = 0;
    }

    void modify(int ql, int qr, int x, int p, int l, int r) {
        if (not p or (ql > r or qr < l)) return;
        push(p, l, r);

        if (ql <= l and qr >= r) {
            tree[p].lazy += x;
            push(p, l, r);
        } else {
            int m = (l + r) / 2;
            modify(ql, qr, x, tree[p].l, l, m);
            modify(ql, qr, x, tree[p].r, m + 1, r);
            tree[p].x = tree[tree[p].l].x + tree[tree[p].r].x;
        }
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p or (ql > r or qr < l)) return 0;
        push(p, l, r);

        if (ql <= l and qr >= r) return tree[p].x;

        int m = (l + r) / 2;
        return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
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
