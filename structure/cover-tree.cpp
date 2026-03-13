struct cover_tree {
    int n;
    vector<int> cnt, len, all;

    void recalc(int i) {
        if (cnt[i] > 0) len[i] = all[i];
        else if (i < n) len[i] = len[i << 1] + len[i << 1 | 1];
        else len[i] = 0;
    }

    cover_tree(vector<int> &x): n(x.size() - 1), cnt(2 * n), len(2 * n), all(2 * n) {
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
        return len[1];
    }
};
