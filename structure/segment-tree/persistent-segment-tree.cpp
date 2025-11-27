struct persistent_segment_tree {
private:
    struct node {
        int v;
        int l, r;

        node(int v, int l, int r): v(v), l(l), r(r) {}
    };

    int n;
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

    int update(int i, int v, int p, int l, int r) {
        if (l == r) return leaf(t[p].v + v);

        int m = (l + r) / 2;
        if (i <= m) return internal(update(i, v, t[p].l, l, m), t[p].r);
        else return internal(t[p].l, update(i, v, t[p].r, m + 1, r));
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p) return 0;
        if (ql > r or qr < l) return 0;
        if (ql <= l and qr >= r) return t[p].v;

        int m = (l + r) / 2;
        return query(ql, qr, t[p].l, l, m) + query(ql, qr, t[p].r, m + 1, r);
    }

    int copy(int ql, int qr, int p, int q, int l, int r) {
        if (ql > r or qr < l) return p;
        if (ql <= l and qr >= r) return q;

        int m = (l + r) / 2;
        return internal(copy(ql, qr, t[p].l, t[q].l, l, m), copy(ql, qr, t[p].r, t[q].r, m + 1, r));
    }

public:
    array<int> r;

    persistent_segment_tree(int n): n(n), t(1) {
        r.reserve(n);
        t.reserve(8 * n);
    }

    void build(array<int> &a) {
        r.push_back(build(a, 0, n - 1));
    }

    void update(int i, int v, int p) {
        r.push_back(update(i, v, p, 0, n - 1));
    }

    int query(int ql, int qr, int p) {
        return query(ql, qr, p, 0, n - 1);
    }

    void copy(int ql, int qr, int p, int q) {
        r.push_back(copy(ql, qr, p, q, 0, n - 1));
    }
};
