// XOR Cover Tree: calculates total length covered by an odd number of intervals
// Time: update O(log N), query O(1) | Space: O(N)
struct xor_cover_tree {
    int n;
    vector<int> all, cnt, len;

    void recalc(int i) {
        int child = 0;
        if (i < n) child = len[i << 1] + len[i << 1 | 1];
        if (cnt[i] & 1) len[i] = all[i] - child;
        else len[i] = child;
    }

    xor_cover_tree(vector<int> &x): n(x.size() - 1), all(2 * n), cnt(2 * n), len(2 * n) {
        for (int i = 0; i < n; ++i) all[n + i] = x[i + 1] - x[i];
        for (int i = n - 1; i > 0; --i) all[i] = all[i << 1] + all[i << 1 | 1];
    }

    void update(int i, int j) {
        int p = i, q = j;
        for (i += n, j += n; i < j; i >>= 1, j >>= 1) {
            if (i & 1) cnt[i] ^= 1, recalc(i++);
            if (j & 1) cnt[--j] ^= 1, recalc(j);
        }
        i = p + n;
        while (i >>= 1) recalc(i);
        j = q + n - 1;
        while (j >>= 1) recalc(j);
    }

    int query() {
        return len[1];
    }
};
