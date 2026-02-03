struct hasher {
    static array<int, 2> base;
    static constexpr array<int, 2> mod = {1e9 + 7, 1e9 + 9};

    int n;
    array<list<int>, 2> pow, hash, rev;

    hasher(str &s): n(s.length()) {
        for (int k = 0; k < 2; ++k) {
            pow[k].assign(n + 1, 1);
            hash[k].assign(n + 1, 0);
            rev[k].assign(n + 2, 0);

            for (int i = 1; i <= n; ++i) {
                pow[k][i] = (base[k] * pow[k][i - 1]) % mod[k];
                hash[k][i] = (s[i - 1] + base[k] * hash[k][i - 1]) % mod[k];
            }

            for (int i = n; i >= 1; --i) {
                rev[k][i] = (s[i - 1] + base[k] * rev[k][i + 1]) % mod[k];
            }
        }
    }

    int hash(int l, int r) {
        ++l, ++r;
        int res = 0;
        for (int k = 0; k < 2; ++k) {
            int curr = (hash[k][r] - (pow[k][r - l + 1] * hash[k][l - 1]) % mod[k]) % mod[k];
            if (curr < 0) curr += mod[k];
            res = (res << 32) | curr;
        }
        return res;
    }

    int reverse(int l, int r) {
        ++l, ++r;
        int res = 0;
        for (int k = 0; k < 2; ++k) {
            int curr = (rev[k][l] - (pow[k][r - l + 1] * rev[k][r + 1]) % mod[k]) % mod[k];
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
