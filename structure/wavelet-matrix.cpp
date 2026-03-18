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
            vector<int> zero; zero.reserve(n);
            vector<int> one; one.reserve(n);
            for (int i = 0; i < n; ++i) {
                bool on = (a[i] >> b) & 1;
                pref[b][i + 1] = pref[b][i];
                if (not on) {
                    pref[b][i + 1] += 1;
                    zero.push_back(a[i]);
                } else {
                    one.push_back(a[i]);
                }
            }
            mid[b] = zero.size();
            copy(zero.begin(), zero.end(), a.begin());
            copy(one.begin(), one.end(), a.begin() + mid[b]);
        }
    }

    int kth(int l, int r, int k) {
        int x = 0;
        for (int b = log; b >= 0; --b) {
            int z_l = pref[b][l];
            int z_r = pref[b][r + 1];
            int z = z_r - z_l;

            if (k < z) {
                l = z_l;
                r = z_r - 1;
            } else {
                x |= 1LL << b;
                l += mid[b] - z_l;
                r += mid[b] - z_r;
                k -= z;
            }
        }
        return x;
    }

    int less_or_equal(int l, int r, int x) {
        int c = 0;
        for (int b = log; b >= 0; --b) {
            int z_l = pref[b][l];
            int z_r = pref[b][r + 1];
            int z = z_r - z_l;

            if (((x >> b) & 1) == 0) {
                l = z_l;
                r = z_r - 1;
            } else {
                c += z;
                l += mid[b] - z_l;
                r += mid[b] - z_r;
            }
        }
        if (l <= r) c += r - l + 1;
        return c;
    }
};
