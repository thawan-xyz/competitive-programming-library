struct persistent_segment_tree {
private:
    struct node {
        int x, l, r;

        node(int x, int l = 0, int r = 0): x(x), l(l), r(r) {}
    };

    int n;
    array<node> tree;

    int terminal(int x) {
        int i = tree.size();
        tree.push_back(node(x));
        return i;
    }

    int internal(int l, int r) {
        int i = tree.size();
        tree.push_back(node(tree[l].x + tree[r].x, l, r));
        return i;
    }

    int build(array<int> &a, int l, int r) {
        if (l == r) return terminal(a[l]);

        int m = (l + r) / 2;
        return internal(build(a, l, m), build(a, m + 1, r));
    }

    int update(int i, int x, int p, int l, int r) {
        if (l == r) return terminal(tree[p].x + x);

        int m = (l + r) / 2;
        if (i <= m) return internal(update(i, x, tree[p].l, l, m), tree[p].r);
        else return internal(tree[p].l, update(i, x, tree[p].r, m + 1, r));
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p or (ql > r or qr < l)) return 0;

        if (ql <= l and qr >= r) return tree[p].x;

        int m = (l + r) / 2;
        return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
    }

    int copy(int ql, int qr, int p, int q, int l, int r) {
        if (ql > r or qr < l) return p;

        if (ql <= l and qr >= r) return q;

        int m = (l + r) / 2;
        return internal(copy(ql, qr, tree[p].l, tree[q].l, l, m), copy(ql, qr, tree[p].r, tree[q].r, m + 1, r));
    }

public:
    array<int> root;

    persistent_segment_tree(int n): n(n), tree(1) {
        root.reserve(n);
        tree.reserve(8 * n);
    }

    void build(array<int> &a) {
        root.push_back(build(a, 0, n - 1));
    }

    void update(int i, int x, int p) {
        root.push_back(update(i, x, p, 0, n - 1));
    }

    int query(int l, int r, int p) {
        return query(l, r, p, 0, n - 1);
    }

    void copy(int l, int r, int p, int q) {
        root.push_back(copy(l, r, p, q, 0, n - 1));
    }
};
