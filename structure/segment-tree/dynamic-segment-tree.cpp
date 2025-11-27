struct dynamic_segment_tree {
private:
    struct node {
        int v;
        int l, r;

        node(int v, int l, int r): v(v), l(l), r(r) {}
    };

    int n, r;
    array<node> t;

    int leaf(int v) {
        int i = t.size();
        t.push_back(node(v, 0, 0));
        return i;
    }

    int internal(int l, int r) {
        int i = t.size();
        t.push_back(node(t[l].v + t[r].v, l, r));
        return i;
    }

    int build(array<int> &a, int l, int r) {
        if (l == r) return leaf(a[l]);

        int m = (l + r) / 2;
        return internal(build(a, l, m), build(a, m + 1, r));
    }

    void update(int i, int v, int p, int l, int r) {
        if (l == r) {
            t[p].v += v;
            return;
        }

        int m = (l + r) / 2;
        if (i <= m) {
            update(i, v, t[p].l, l, m);
        } else {
            update(i, v, t[p].r, m + 1, r);
        }
        t[p].v = t[t[p].l].v + t[t[p].r].v;
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p) return 0;
        if (ql > r or qr < l) return 0;
        if (ql <= l and qr >= r) return t[p].v;

        int m = (l + r) / 2;
        return query(ql, qr, t[p].l, l, m) + query(ql, qr, t[p].r, m + 1, r);
    }

public:
    dynamic_segment_tree(int n): n(n), t(1) {
        t.reserve(2 * n + 5);
    }

    void build(array<int> &a) {
        r = build(a, 0, n - 1);
    }

    void update(int i, int v) {
        update(i, v, r, 0, n - 1);
    }

    int query(int ql, int qr) {
        return query(ql, qr, r, 0, n - 1);
    }
};
