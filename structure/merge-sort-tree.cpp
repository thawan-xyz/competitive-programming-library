struct segment_tree {
private:
    struct node {
        list<int> a;
        int l, r;

        node(int l = 0, int r = 0): l(l), r(r) {}
    };

    int n, root;
    list<node> tree;

    int build(list<int> &a, int l, int r) {
        int p = tree.size();
        tree.push_back(node());
        if (l == r) {
            tree[p].a = {a[l]};
        } else {
            int m = (l + r) / 2;
            tree[p].l = build(a, l, m);
            tree[p].r = build(a, m + 1, r);
            tree[p].a.resize(tree[tree[p].l].a.size() + tree[tree[p].r].a.size());
            merge(tree[tree[p].l].a.begin(), tree[tree[p].l].a.end(), tree[tree[p].r].a.begin(), tree[tree[p].r].a.end(), tree[p].a.begin());
        }
        return p;
    }

    int count_less_equal(int ql, int qr, int x, int p, int l, int r) {
        if (not p or (ql > r or qr < l)) return 0;

        if (ql <= l and qr >= r) return upper_bound(tree[p].a.begin(), tree[p].a.end(), x) - tree[p].a.begin();

        int m = (l + r) / 2;
        return count_less_equal(ql, qr, x, tree[p].l, l, m) + count_less_equal(ql, qr, x, tree[p].r, m + 1, r);
    }

public:
    segment_tree(list<int> &a): n(a.size()), tree(1) {
        tree.reserve(2 * n);
        root = build(a, 0, n - 1);
    }

    int count_less_equal(int l, int r, int x) {
        return count_less_equal(l, r, x, root, 0, n - 1);
    }
};
