const int mod = (1LL << 61) - 1;
const int128 base = uniform_int_distribution<int>(256, mod - 1)(rng);

struct info {
    int len = 0, norm = 0, rev = 0;
    int128 pow = 1;

    bool operator==(const info &o) const {
        return len == o.len and norm == o.norm;
    }
};

struct hasher {
    int n;
    vector<int> pre, suf;
    vector<int128> pows;

    hasher(const string &s): n(s.size()), pre(n + 1), suf(n + 1), pows(n + 1, 1) {
        for (int i = 0; i < n; ++i) {
            pre[i + 1] = (pre[i] * base + s[i]) % mod;
            pows[i + 1] = pows[i] * base % mod;
        }
        for (int i = n - 1; i >= 0; --i) suf[i] = (suf[i + 1] * base + s[i]) % mod;
    }

    info query(int l, int r) {
        info h;
        h.len = r - l + 1;
        h.pow = pows[h.len];
        h.norm = (pre[r + 1] - pre[l] * h.pow % mod + mod) % mod;
        h.rev = (suf[l] - suf[r + 1] * h.pow % mod + mod) % mod;
        return h;
    }
};
