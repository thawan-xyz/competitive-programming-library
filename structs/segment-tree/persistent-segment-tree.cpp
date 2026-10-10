struct persistent_segment_tree {
private:
    struct node {
        int x = 0;
        int l = 0, r = 0;
    };

    int n;
    vector<node> tree;

    int clone(int p) {
        tree.push_back(tree[p]);
        return tree.size() - 1;
    }

    int build(vector<int> &a, int l, int r) {
        int p = tree.size();
        tree.emplace_back();
        if (l == r) {
            tree[p].x = a[l];
            return p;
        }
        int m = (l + r) / 2;
        tree[p].l = build(a, l, m);
        tree[p].r = build(a, m + 1, r);
        tree[p].x = tree[tree[p].l].x + tree[tree[p].r].x;
        return p;
    }

    int update(int i, int x, int p, int l, int r) {
        int c = clone(p);
        if (l == r) {
            tree[c].x = x;
            return c;
        }
        int m = (l + r) / 2;
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
        if (qr < l or r < ql) return 0;
        if (ql <= l and r <= qr) return tree[p].x;
        int m = (l + r) / 2;
        return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
    }

    int copy_range(int ql, int qr, int s, int t, int l, int r) {
        if (qr < l or r < ql) return t;
        if (ql <= l and r <= qr) return s;
        int c = clone(t);
        int m = (l + r) / 2;
        int nl = copy_range(ql, qr, tree[s].l, tree[t].l, l, m);
        tree[c].l = nl;
        int nr = copy_range(ql, qr, tree[s].r, tree[t].r, m + 1, r);
        tree[c].r = nr;
        tree[c].x = tree[tree[c].l].x + tree[tree[c].r].x;
        return c;
    }

public:
    vector<int> roots;

    persistent_segment_tree(vector<int> &a, int q = 0): n(a.size()) {
        tree.reserve(4 * n + 20 * q);
        roots.push_back(build(a, 0, n - 1));
    }

    void update(int i, int x, int v = -1) {
        if (v == -1) v = roots.size() - 1;
        roots.push_back(update(i, x, roots[v], 0, n - 1));
    }

    int query(int ql, int qr, int v = -1) {
        if (v == -1) v = roots.size() - 1;
        return query(ql, qr, roots[v], 0, n - 1);
    }

    void copy_range(int ql, int qr, int s, int t = -1) {
        if (t == -1) t = roots.size() - 1;
        roots.push_back(copy_range(ql, qr, roots[s], roots[t], 0, n - 1));
    }
};
