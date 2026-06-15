// Iterative K-Cover Segment Tree: calculates total length covered by at least K intervals
// Time: update O(K log N), query O(1) | Space: O(N * K)
struct k_cover_tree {
    int n, k;
    vector<int> all, cnt;
    vector<vector<int>> len;

    void recalc(int i) {
        vector<int> base(k + 1);
        base[0] = all[i];
        if (i < n) for (int h = 1; h <= k; ++h) base[h] = len[i << 1][h] + len[i << 1 | 1][h];
        for (int h = 1; h <= k; ++h) len[i][h] = base[max<int>(0, h - cnt[i])];
    }

    k_cover_tree(int k, vector<int> &x): n(x.size() - 1), k(k), all(2 * n), cnt(2 * n), len(2 * n, vector<int>(k + 1)) {
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
        return len[1][k];
    }
};
