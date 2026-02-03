struct hasher {
    static array<int, 2> base;
    static constexpr array<int, 2> mod = {1000000007, 1000000009};

    int n;
    array<list<int>, 2> pow, pref, suf;

    hasher(str &s): n(s.length()) {
        for (int k = 0; k < 2; ++k) {
            pow[k].assign(n + 1, 1);
            pref[k].assign(n + 1, 0);
            suf[k].assign(n + 2, 0);

            for (int i = 1; i <= n; ++i) {
                pow[k][i] = (base[k] * pow[k][i - 1]) % mod[k];
                pref[k][i] = (s[i - 1] + base[k] * pref[k][i - 1]) % mod[k];
            }

            for (int i = n; i >= 1; --i) {
                suf[k][i] = (s[i - 1] + base[k] * suf[k][i + 1]) % mod[k];
            }
        }
    }

    int hash(int l, int r) {
        ++l, ++r;
        int res = 0;
        for (int k = 0; k < 2; ++k) {
            int curr = (pref[k][r] - (pow[k][r - l + 1] * pref[k][l - 1]) % mod[k]) % mod[k];
            if (curr < 0) curr += mod[k];
            res = (res << 32) | curr;
        }
        return res;
    }

    int reverse(int l, int r) {
        ++l, ++r;
        int res = 0;
        for (int k = 0; k < 2; ++k) {
            int curr = (suf[k][l] - (pow[k][r - l + 1] * suf[k][r + 1]) % mod[k]) % mod[k];
            if (curr < 0) curr += mod[k];
            res = (res << 32) | curr;
        }
        return res;
    }
};

array<int, 2> hasher::base = []{
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    array<int, 2> base;
    base[0] = 41;
    base[1] = uniform_int_distribution<int>(256, hasher::mod[1] - 1)(rng);
    return base;
}();
