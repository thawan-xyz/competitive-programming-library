const array<int, 2> base = {41, 53};
const array<int, 2> mod = {1000000007, 1000000009};

struct hasher {
    int n;
    vector<array<int, 2>> pow;
    vector<array<int, 2>> pref, suf;

    hasher(const string &s): n(s.length()), pow(n + 1), pref(n + 1), suf(n + 2) {
        pow[0] = {1, 1};
        for (int i = 0; i < n; ++i) for (int j : {0, 1}) {
            pow[i + 1][j] = (pow[i][j] * base[j]) % mod[j];
            pref[i + 1][j] = (pref[i][j] * base[j] + s[i]) % mod[j];
            suf[n - i][j] = (suf[n - i + 1][j] * base[j] + s[n - i - 1]) % mod[j];
        }
    }

    int get(vector<array<int, 2>> &h, int l, int r) {
        array<int, 2> a;
        for (int i : {0, 1}) {
            a[i] = (h[r][i] - h[l][i] * pow[abs(r - l)][i]) % mod[i];
            if (a[i] < 0) a[i] += mod[i];
        }
        return (a[0] << 32) | a[1];
    }

    int normal(int l, int r) {
        return get(pref, l, r + 1);
    }

    int reverse(int l, int r) {
        return get(suf, r + 2, l + 1);
    }
};
