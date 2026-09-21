// Cover Tree: calculates total length covered by at least one interval
// Time: update O(log N), query O(1) | Space: O(N)
struct cover_tree {
    int n;
    vector<int> all, cnt, curr;

    void recalc(int i) {
        if (cnt[i] > 0) curr[i] = all[i];
        else if (i < n) curr[i] = curr[i << 1] + curr[i << 1 | 1];
        else curr[i] = 0;
    }

    cover_tree(vector<int> &x): n(x.size() - 1), all(2 * n), cnt(2 * n), curr(2 * n) {
        for (int i = 0; i < n; ++i) all[n + i] = x[i + 1] - x[i];
        for (int i = n - 1; i > 0; --i) all[i] = all[i << 1] + all[i << 1 | 1];
    }

    void update(int i, int j, int x) {
        int p = i, q = j;
        for (i += n, j += n; i < j; i >>= 1, j >>= 1) {
            if (i & 1) cnt[i] += x, recalc(i++);
            if (j & 1) cnt[--j] += x, recalc(j);
        }
        i = p + n;
        while (i >>= 1) recalc(i);
        j = q + n - 1;
        while (j >>= 1) recalc(j);
    }

    int query() {
        return curr[1];
    }
};

struct cover_tree {
    int n;
    vector<int> all, cnt, curr, xs;

    void build(int p, int l, int r) {
        all[p] = xs[r] - xs[l];
        if (l + 1 == r) return;
        int m = (l + r) / 2;
        build(2 * p, l, m);
        build(2 * p + 1, m, r);
    }

    void recalc(int p, int l, int r) {
        if (cnt[p] > 0) {
            curr[p] = all[p];
        } else if (l + 1 == r) {
            curr[p] = 0;
        } else {
            curr[p] = curr[2 * p] + curr[2 * p + 1];
        }
    }

    cover_tree(vector<int> &x): n(x.size() - 1), all(4 * n), cnt(4 * n), curr(4 * n), xs(x) {
        build(1, 0, n);
    }

    void update(int p, int l, int r, int ql, int qr, int val) {
        if (qr <= l or r <= ql) return;
        if (ql <= l and r <= qr) {
            cnt[p] += val;
            recalc(p, l, r);
            return;
        }
        int m = (l + r) / 2;
        update(2 * p, l, m, ql, qr, val);
        update(2 * p + 1, m, r, ql, qr, val);
        recalc(p, l, r);
    }

    int query(int p, int l, int r, int ql, int qr, int c) {
        if (qr <= l or r <= ql) return 0;
        if (ql <= l and r <= qr) {
            if (cnt[p] > 0 or c > 0) return all[p];
            return curr[p];
        }
        int m = (l + r) / 2;
        return query(2 * p, l, m, ql, qr, c + cnt[p]) + query(2 * p + 1, m, r, ql, qr, c + cnt[p]);
    }

    void update(int l, int r, int v) {
        update(1, 0, n, l, r, v);
    }

    int query(int l, int r) {
        return query(1, 0, n, l, r, 0);
    }

    int query() {
        return curr[1];
    }
};
