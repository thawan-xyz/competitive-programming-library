struct segment_tree {
private:
    struct node {
        int x, l, r;

        node(int x, int l = 0, int r = 0): x(x), l(l), r(r) {}
    };

    int n, root;
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

    void update(int i, int x, int p, int l, int r) {
        if (not p or (i > r or i < l)) return;

        if (l == r) return void(tree[p].x += x);

        int m = (l + r) / 2;
        update(i, x, tree[p].l, l, m), update(i, x, tree[p].r, m + 1, r);
        tree[p].x = tree[tree[p].l].x + tree[tree[p].r].x;
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p or (ql > r or qr < l)) return 0;

        if (ql <= l and qr >= r) return tree[p].x;

        int m = (l + r) / 2;
        return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
    }

public:
    segment_tree(int n): n(n), tree(1) {
        tree.reserve(2 * n + 5);
    }

    void build(array<int> &a) {
        root = build(a, 0, n - 1);
    }

    void update(int i, int x) {
        update(i, x, root, 0, n - 1);
    }

    int query(int l, int r) {
        return query(l, r, root, 0, n - 1);
    }
};
