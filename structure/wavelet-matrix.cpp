// Wavelet Matrix: Range Quantile, Range Frequency, K-th smallest
// Time: Build O(N log V) | Queries O(log V) | Space: O(N log V)
// Note: Coordinate compression is REQUIRED before building.
struct wavelet_matrix {
    int n, log;
    vector<vector<int>> pref;
    vector<int> mid;

    wavelet_matrix(vector<int> a) {
        n = a.size();
        log = __lg(*max_element(a.begin(), a.end()) + 1);
        pref.assign(log + 1, vector<int>(n + 1));
        mid.resize(log + 1);

        for (int b = log; b >= 0; --b) {
            vector<int> z; z.reserve(n);
            vector<int> o; o.reserve(n);
            for (int i = 0; i < n; ++i) {
                bool on = (a[i] >> b) & 1;
                pref[b][i + 1] = pref[b][i];
                if (not on) {
                    pref[b][i + 1] += 1;
                    z.push_back(a[i]);
                } else {
                    o.push_back(a[i]);
                }
            }
            mid[b] = z.size();
            copy(z.begin(), z.end(), a.begin());
            copy(o.begin(), o.end(), a.begin() + mid[b]);
        }
    }

    int kth(int i, int j, int k) {
        int x = 0;
        for (int b = log; b >= 0; --b) {
            int l = pref[b][i];
            int r = pref[b][j + 1];
            int z = r - l;

            if (k < z) {
                i = l;
                j = r - 1;
            } else {
                x |= 1LL << b;
                k -= z;
                i += mid[b] - l;
                j += mid[b] - r;
            }
        }
        return x;
    }

    int less_or_equal(int i, int j, int x) {
        int c = 0;
        for (int b = log; b >= 0; --b) {
            int l = pref[b][i];
            int r = pref[b][j + 1];
            int z = r - l;

            if (((x >> b) & 1) == 0) {
                i = l;
                j = r - 1;
            } else {
                c += z;
                i += mid[b] - l;
                j += mid[b] - r;
            }
        }
        if (i <= j) c += j - i + 1;
        return c;
    }
};
