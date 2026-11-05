// Wavelet Matrix: range quantile, range frequency, k-th smallest
// Time: build O(N log V) | Queries O(log V) | Space: O(N log V)
// Note: kth is 0-indexed
struct wavelet_matrix {
    int n, log = 1;
    vector<int> vals, zeros;
    vector<vector<int>> pref;

    wavelet_matrix(vector<int> a): n(a.size()), vals(a) {
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
        for (int &x : a) x = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
        while ((1 << log) < vals.size()) log++;
        zeros.resize(log);
        pref.assign(log, vector<int>(n + 1));
        for (int b = log - 1; b >= 0; --b) {
            for (int i = 0; i < n; ++i) pref[b][i + 1] = pref[b][i] + !(a[i] >> b & 1);
            zeros[b] = stable_partition(a.begin(), a.end(), [&](int x) { return !(x >> b & 1); }) - a.begin();
        }
    }

    int kth(int l, int r, int k) {
        int x = 0;
        r++;
        for (int b = log - 1; b >= 0; --b) {
            int zl = pref[b][l], zr = pref[b][r];
            if (k < zr - zl) l = zl, r = zr;
            else x |= 1 << b, k -= zr - zl, l += zeros[b] - zl, r += zeros[b] - zr;
        }
        return vals[x];
    }

    int less_equal(int l, int r, int x) {
        int t = upper_bound(vals.begin(), vals.end(), x) - vals.begin(), c = 0;
        if (t == (1 << log)) return r - l + 1;
        r++;
        for (int b = log - 1; b >= 0; --b) {
            int zl = pref[b][l], zr = pref[b][r];
            if (t >> b & 1) c += zr - zl, l += zeros[b] - zl, r += zeros[b] - zr;
            else l = zl, r = zr;
        }
        return c;
    }
};
