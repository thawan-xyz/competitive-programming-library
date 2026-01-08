struct segment_tree {
private:
    struct node {
        array<int> a;
        int l, r;

        node(array<int> a = {}, int l = 0, int r = 0): a(move(a)), l(l), r(r) {}
    };

    int n, root;
    array<node> tree;

    int terminal(int x) {
        int i = tree.size();
        tree.push_back(node({x}));
        return i;
    }

    int internal(int l, int r) {
        int i = tree.size();
        array<int> a; a.reserve(tree[l].a.size() + tree[r].a.size());
        merge(tree[l].a.begin(), tree[l].a.end(), tree[r].a.begin(), tree[r].a.end(), back_inserter(a));
        tree.push_back(node(move(a), l, r));
        return i;
    }

    int build(array<int> &a, int l, int r) {
        if (l == r) return terminal(a[l]);

        int m = (l + r) / 2;
        return internal(build(a, l, m), build(a, m + 1, r));
    }

    int count_less_equal(int ql, int qr, int x, int p, int l, int r) {
        if (not p or (ql > r or qr < l)) return 0;

        if (ql <= l and qr >= r) return upper_bound(tree[p].a.begin(), tree[p].a.end(), x) - tree[p].a.begin();

        int m = (l + r) / 2;
        return count_less_equal(ql, qr, x, tree[p].l, l, m) + count_less_equal(ql, qr, x, tree[p].r, m + 1, r);
    }

public:
    segment_tree(array<int> &a): n(a.size()), tree(1) {
        tree.reserve(2 * n + 5);
        root = build(a, 0, n - 1);
    }

    int count_less_equal(int l, int r, int x) {
        return count_less_equal(l, r, x, root, 0, n - 1);
    }
};
