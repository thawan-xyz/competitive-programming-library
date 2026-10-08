const array<int, 2> base = {41, 53};
const array<int, 2> mod = {1000000007, 1000000009};

vector<array<int, 2>> pows = {{{1, 1}}};

void extend(int n) {
    while (pows.size() <= n) {
        array<int, 2> back = pows.back();
        array<int, 2> curr = {(back[0] * base[0]) % mod[0], (back[1] * base[1]) % mod[1]};
        pows.push_back(curr);
    }
}

struct block {
    int len = 0;
    array<int, 2> ord = {};
    array<int, 2> rev = {};

    bool operator==(const block &o) const {
        return len == o.len and ord == o.ord;
    }
};

struct hasher {
    int n;
    vector<array<int, 2>> pref, suf;
    
    hasher(const string &s): n(s.length()), pref(n + 1), suf(n + 2) {
        extend(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= 1; ++j) {
                pref[i + 1][j] = (pref[i][j] * base[j] + s[i]) % mod[j];
                suf[n - i][j] = (suf[n - i + 1][j] * base[j] + s[n - i - 1]) % mod[j];
            }
        }
    }

    block query(int l, int r) const {
        block h;
        h.len = r - l + 1;
        for (int i = 0; i <= 1; ++i) {
            h.ord[i] = (pref[r + 1][i] - pref[l][i] * pows[h.len][i]) % mod[i];
            h.ord[i] = (h.ord[i] + mod[i]) % mod[i];
            h.rev[i] = (suf[l + 1][i] - suf[r + 2][i] * pows[h.len][i]) % mod[i];
            h.rev[i] = (h.rev[i] + mod[i]) % mod[i];
        }
        return h;
    }
};
