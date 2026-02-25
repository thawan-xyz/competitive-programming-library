struct cover_tree {
private:
    int n;
    list<int> x;
    list<int> count;
    list<int> length;

    void modify(int ql, int qr, int v, int p, int l, int r) {
        if (ql <= l and r <= qr) {
            count[p] += v;
        } else {
            int m = (l + r) / 2;
            if (ql < m) modify(ql, qr, v, 2 * p, l, m);
            if (qr > m) modify(ql, qr, v, 2 * p + 1, m, r);
        }

        if (count[p] > 0) {
            length[p] = x[r] - x[l];
        } else {
            if (l + 1 == r) {
                length[p] = 0;
            } else {
                length[p] = length[2 * p] + length[2 * p + 1];
            }
        }
    }

public:
    cover_tree(list<int> &x): n(x.size()), x(x), count(4 * n), length(4 * n) {}

    void modify(int l, int r, int v) {
        modify(l, r, v, 1, 0, n - 1);
    }

    int query() {
        return length[1];
    }
};
