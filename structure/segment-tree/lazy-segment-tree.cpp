struct lazy_segment_tree {
private:
    int n;
    list<int> tree;
    list<int> lazy;

    void build(list<int> &a, int p, int l, int r) {
        if (l == r) {
            tree[p] = a[l];
        } else {
            int m = (l + r) / 2;
            build(a, 2 * p, l, m);
            build(a, (2 * p) + 1, m + 1, r);
            tree[p] = tree[2 * p] + tree[(2 * p) + 1];
        }
    }

    void push(int p, int l, int r) {
        if (lazy[p] != 0) {
            int m = (l + r) / 2;
            tree[2 * p] += lazy[p] * (m - l + 1);
            lazy[2 * p] += lazy[p];
            tree[(2 * p) + 1] += lazy[p] * (r - m);
            lazy[(2 * p) + 1] += lazy[p];
            lazy[p] = 0;
        }
    }

    void update(int ql, int qr, int x, int p, int l, int r) {
        if (ql <= l and r <= qr) {
            tree[p] += x * (r - l + 1);
            lazy[p] += x;
        } else {
            push(p, l, r);
            int m = (l + r) / 2;
            if (ql <= m) update(ql, qr, x, 2 * p, l, m);
            if (qr > m) update(ql, qr, x, (2 * p) + 1, m + 1, r);
            tree[p] = tree[2 * p] + tree[(2 * p) + 1];
        }
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (ql <= l and r <= qr) {
            return tree[p];
        } else {
            push(p, l, r);
            int m = (l + r) / 2;
            int answer = 0;
            if (ql <= m) answer += query(ql, qr, 2 * p, l, m);
            if (qr > m) answer += query(ql, qr, (2 * p) + 1, m + 1, r);
            return answer;
        }
    }

public:
    lazy_segment_tree(int n): n(n), tree(4 * n), lazy(4 * n) {}

    lazy_segment_tree(list<int> &a): n(a.size()), tree(4 * n), lazy(4 * n) {
        build(a, 1, 0, n - 1);
    }

    void update(int l, int r, int x) {
        update(l, r, x, 1, 0, n - 1);
    }

    int query(int l, int r) {
        return query(l, r, 1, 0, n - 1);
    }
};
