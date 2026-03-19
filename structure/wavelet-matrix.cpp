// Wavelet Matrix: Range Quantile, Range Frequency, K-th smallest
// Time: Build O(N log V) | Queries O(log V) | Space: O(N log V)
// Note: Coordinate compression is REQUIRED before building.
struct wavelet_matrix {
    int n, log;
    vector<vector<int>> pref;
    vector<int> mid;

    wavelet_matrix(vector<int> a): n(a.size()), log(__lg(*max_element(a.begin(), a.end()) | 1)), pref(log + 1, vector<int>(n + 1)), mid(log + 1) {
        for (int b = log; b >= 0; --b) {
            for (int i = 0; i < n; ++i) pref[b][i + 1] = pref[b][i] + (((a[i] >> b) & 1) == 0);
            mid[b] = stable_partition(a.begin(), a.end(), [&](int x) { return ((x >> b) & 1) == 0;}) - a.begin();
        }
    }

    int kth(int i, int j, int k) {
        int x = 0;
        for (int b = log; b >= 0; --b) {
            int l = pref[b][i], r = pref[b][j + 1], z = r - l;
            if (k < z) i = l, j = r - 1;
            else x |= 1LL << b, i += mid[b] - l, j += mid[b] - r, k -= z;
        }
        return x;
    }

    int less_or_equal(int i, int j, int x) {
        int c = 0;
        for (int b = log; b >= 0; --b) {
            int l = pref[b][i], r = pref[b][j + 1], z = r - l;
            if (((x >> b) & 1) == 0) i = l, j = r - 1;
            else c += z, i += mid[b] - l, j += mid[b] - r;
        }
        if (i <= j) c += j - i + 1;
        return c;
    }
};
