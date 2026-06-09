struct segment_tree {
private:
    int n;
    vector<int> tree;

    void build(vector<int> &a, int p, int l, int r) {
        if (l == r) {
            tree[p] = a[l];
        } else {
            int m = (l + r) / 2;
            build(a, 2 * p, l, m);
            build(a, (2 * p) + 1, m + 1, r);
            tree[p] = tree[2 * p] + tree[(2 * p) + 1];
        }
    }

    void update(int i, int x, int p, int l, int r) {
        if (l == r) {
            tree[p] += x;
        } else {
            int m = (l + r) / 2;
            if (i <= m) update(i, x, 2 * p, l, m);
            if (i > m) update(i, x, (2 * p) + 1, m + 1, r);
            tree[p] = tree[2 * p] + tree[(2 * p) + 1];
        }
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (ql <= l and r <= qr) {
            return tree[p];
        } else {
            int m = (l + r) / 2;
            int answer = 0;
            if (ql <= m) answer += query(ql, qr, 2 * p, l, m);
            if (qr > m) answer += query(ql, qr, (2 * p) + 1, m + 1, r);
            return answer;
        }
    }

public:
    segment_tree(int n): n(n), tree(4 * n) {}

    segment_tree(vector<int> &a): n(a.size()), tree(4 * n) {
        build(a, 1, 0, n - 1);
    }

    void update(int i, int x) {
        update(i, x, 1, 0, n - 1);
    }

    int query(int l, int r) {
        return query(l, r, 1, 0, n - 1);
    }
};
