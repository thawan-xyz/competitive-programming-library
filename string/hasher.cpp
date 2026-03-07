struct hasher {
    static constexpr array<int, 2> base = {41, 53};
    static constexpr array<int, 2> mod = {1000000007, 1000000009};

    int n;
    vector<array<int, 2>> pow;
    vector<array<int, 2>> pref, suf;

    hasher(const string &s): n(s.length()), pow(n + 1), pref(n + 1), suf(n + 2) {
        pow[0][0] = pow[0][1] = 1;
        for (int i = 1; i <= n; ++i) {
            pow[i][0] = (pow[i - 1][0] * base[0]) % mod[0];
            pow[i][1] = (pow[i - 1][1] * base[1]) % mod[1];
        }
        pref[0][0] = pref[0][1] = 0;
        for (int i = 1; i <= n; ++i) {
            pref[i][0] = (pref[i - 1][0] * base[0] + s[i - 1]) % mod[0];
            pref[i][1] = (pref[i - 1][1] * base[1] + s[i - 1]) % mod[1];
        }
        suf[n + 1][0] = suf[n + 1][1] = 0;
        for (int i = n; i >= 1; --i) {
            suf[i][0] = (suf[i + 1][0] * base[0] + s[i - 1]) % mod[0];
            suf[i][1] = (suf[i + 1][1] * base[1] + s[i - 1]) % mod[1];
        }
    }

    array<int, 2> f_hash(int l, int r) {
        ++l, ++r;
        int len = r - l + 1;
        array<int, 2> res;
        res[0] = (pref[r][0] - (pref[l - 1][0] * pow[len][0])) % mod[0];
        if (res[0] < 0) res[0] += mod[0];
        res[1] = (pref[r][1] - (pref[l - 1][1] * pow[len][1])) % mod[1];
        if (res[1] < 0) res[1] += mod[1];
        return res;
    }

    array<int, 2> r_hash(int l, int r) {
        ++l, ++r;
        int len = r - l + 1;
        array<int, 2> res;
        res[0] = (suf[l][0] - (suf[r + 1][0] * pow[len][0])) % mod[0];
        if (res[0] < 0) res[0] += mod[0];
        res[1] = (suf[l][1] - (suf[r + 1][1] * pow[len][1])) % mod[1];
        if (res[1] < 0) res[1] += mod[1];
        return res;
    }

    bool palindrome(int l, int r) {
        if (l >= r) return true;
        return f_hash(l, r) == r_hash(l, r);
    }
};
