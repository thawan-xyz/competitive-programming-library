// Cover Tree: total length covered by at least one interval, or by an odd number of them
// Time: update O(log N), query O(1) | Space: O(N)
// Note: x = sorted coordinates, update(l, r, k) adds k to the count of [x[l], x[r]) | odd = true counts only the length covered an odd number of times
struct cover_tree {
    int n;
    bool odd;
    vector<int> len, cnt, cov;

    cover_tree(const vector<int> &x, bool odd): n(x.size() - 1), odd(odd), len(2 * n), cnt(2 * n), cov(2 * n) {
        for (int i = 0; i < n; ++i) len[n + i] = x[i + 1] - x[i];
        for (int i = n - 1; i > 0; --i) len[i] = len[2 * i] + len[2 * i + 1];
    }

    void pull(int i) {
        if (not odd and cnt[i] > 0) {
            cov[i] = len[i];
            return;
        }
        int child = (i < n) ? cov[2 * i] + cov[2 * i + 1] : 0;
        if (odd and (cnt[i] & 1)) cov[i] = len[i] - child;
        else cov[i] = child;
    }

    void update(int l, int r, int k) {
        for (int i = l + n, j = r + n; i < j; i >>= 1, j >>= 1) {
            if (i & 1) cnt[i] += k, pull(i++);
            if (j & 1) cnt[--j] += k, pull(j);
        }
        for (int i = (l + n) >> 1; i > 0; i >>= 1) pull(i);
        for (int i = (r - 1 + n) >> 1; i > 0; i >>= 1) pull(i);
    }

    int query() {
        return cov[1];
    }
};
