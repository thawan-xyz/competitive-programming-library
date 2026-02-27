struct cover_tree {
private:
    int n;
    vector<int> x;
    vector<int> count;
    vector<int> len;

    void modify(int ql, int qr, int v, int p, int l, int r) {
        if (ql <= l and r <= qr) {
            count[p] += v;
        } else {
            int m = (l + r) / 2;
            if (ql < m) modify(ql, qr, v, 2 * p, l, m);
            if (qr > m) modify(ql, qr, v, (2 * p) + 1, m, r);
        }

        if (count[p] > 0) {
            len[p] = x[r] - x[l];
        } else {
            if (l == r - 1) {
                len[p] = 0;
            } else {
                len[p] = len[2 * p] + len[(2 * p) + 1];
            }
        }
    }

public:
    cover_tree(vector<int> &x): n(x.size()), x(x), count(4 * n), len(4 * n) {}

    void modify(int l, int r, int v) {
        modify(l, r, v, 1, 0, n - 1);
    }

    int query() {
        return len[1];
    }
};
