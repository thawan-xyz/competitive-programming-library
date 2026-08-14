const array<int, 2> base = {41, 53};
const array<int, 2> mod = {1000000007, 1000000009};

const int maxn = 1e6;
array<array<int, 2>, maxn + 1> pwr;

void init() {
    pwr[0] = {1, 1};
    for (int i = 1; i <= maxn; ++i) {
        for (int j = 0; j <= 1; ++j) {
            pwr[i][j] = (pwr[i - 1][j] * base[j]) % mod[j];
        }
    }
}

struct info {
    int len;
    array<int, 2> ord, rev;

    info(char c = 0) {
        len = c != 0;
        for (int i = 0; i <= 1; ++i) {
            ord[i] = c % mod[i];
            rev[i] = c % mod[i];
        }
    }

    bool operator==(const info &o) const {
        return len == o.len and ord == o.ord;
    }
};

info combine(const info &l, const info &r) {
    info m;
    m.len = l.len + r.len;
    for (int i = 0; i <= 1; ++i) {
        m.ord[i] = (l.ord[i] * pwr[r.len][i] + r.ord[i]) % mod[i];
        m.rev[i] = (r.rev[i] * pwr[l.len][i] + l.rev[i]) % mod[i];
    }
    return m;
}

struct hasher {
    int n;
    vector<array<int, 2>> pref, suf;
    
    hasher(string &s): n(s.length()), pref(n + 1), suf(n + 2) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= 1; ++j) {
                pref[i + 1][j] = (pref[i][j] * base[j] + s[i]) % mod[j];
                suf[n - i][j] = (suf[n - i + 1][j] * base[j] + s[n - i - 1]) % mod[j];
            }
        }
    }

    info query(int l, int r) const {
        assert(l <= r);
        info h;
        h.len = r - l + 1;
        for (int i = 0; i <= 1; ++i) {
            h.ord[i] = (pref[r + 1][i] - pref[l][i] * pwr[h.len][i]) % mod[i];
            h.ord[i] = (h.ord[i] + mod[i]) % mod[i];
            h.rev[i] = (suf[l + 1][i] - suf[r + 2][i] * pwr[h.len][i]) % mod[i];
            h.rev[i] = (h.rev[i] + mod[i]) % mod[i];
        }
        return h;
    }
};
