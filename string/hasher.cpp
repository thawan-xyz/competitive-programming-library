const array<int, 2> BASE = {41, 53};
const array<int, 2> MOD = {1000000007, 1000000009};

vector<array<int, 2>> POW = {{1, 1}};

void compute_pow(int n) {
    while (POW.size() <= n) {
        array<int, 2> NEXT;
        for (int i : {0, 1}) NEXT[i] = (POW.back()[i] * BASE[i]) % MOD[i];
        POW.push_back(NEXT);
    }
}

struct hash_val {
    int len;
    array<int, 2> ord, rev;

    bool operator==(const hash_val &o) const {
        return len == o.len and ord == o.ord;
    }
};

hash_val combine(const hash_val &l, const hash_val &r) {
    compute_pow(max(l.len, r.len));
    hash_val m;
    m.len = l.len + r.len;
    for (int i : {0, 1}) {
        m.ord[i] = (l.ord[i] * POW[r.len][i] + r.ord[i]) % MOD[i];
        m.rev[i] = (r.rev[i] * POW[l.len][i] + l.rev[i]) % MOD[i];
    }
    return m;
}

struct hasher {
    int n;
    vector<array<int, 2>> pref, suf;
    
    hasher(string &s): n(s.length()), pref(n + 1), suf(n + 2) {
        compute_pow(n);
        for (int i = 0; i < n; ++i) {
            for (int j : {0, 1}) {
                pref[i + 1][j] = (pref[i][j] * BASE[j] + s[i]) % MOD[j];
                suf[n - i][j] = (suf[n - i + 1][j] * BASE[j] + s[n - i - 1]) % MOD[j];
            }
        }
    }

    hash_val query(int l, int r) const {
        assert(l <= r);
        hash_val h;
        h.len = r - l + 1;
        for (int i : {0, 1}) {
            h.ord[i] = (pref[r + 1][i] - pref[l][i] * POW[h.len][i]) % MOD[i];
            if (h.ord[i] < 0) h.ord[i] += MOD[i];
            h.rev[i] = (suf[l + 1][i] - suf[r + 2][i] * POW[h.len][i]) % MOD[i];
            if (h.rev[i] < 0) h.rev[i] += MOD[i];
        }
        return h;
    }
};
