// Berlekamp-Massey: shortest linear recurrence of a sequence, f[i] = c[0] f[i - 1] + c[1] f[i - 2] + ... + c[L - 1] f[i - L]
// Time: O(N^2) | Space: O(N)
// Note: uses mod_pow | needs at least 2L terms to find a recurrence of length L
vector<int> berlekamp_massey(const vector<int> &f) {
    int n = f.size(), len = 0, gap = 0, last = 1;
    vector<int> cur = {1}, old = {1};
    for (int i = 0; i < n; ++i) {
        gap++;
        int d = 0;
        for (int j = 0; j <= len; ++j) d = (d + cur[j] * f[i - j]) % mod;
        if (d == 0) continue;
        vector<int> temp = cur;
        int scale = d * mod_pow(last, mod - 2, mod) % mod;
        cur.resize(max<int>(cur.size(), old.size() + gap));
        for (int j = 0; j < old.size(); ++j) cur[j + gap] = (cur[j + gap] - scale * old[j] % mod + mod) % mod;
        if (2 * len > i) continue;
        len = i + 1 - len, old = temp, last = d, gap = 0;
    }
    vector<int> c(len);
    for (int j = 0; j < len; ++j) c[j] = (mod - cur[j + 1]) % mod;
    return c;
}

// Kth Term: f[k] of a sequence that follows the recurrence c, from its first L terms
// Time: O(L^2 log K) | Space: O(L)
// Note: 0-indexed | usage: kth_term(f, berlekamp_massey(f), k) | x^k mod the characteristic polynomial gives f[k] as a mix of f[0..L-1]
int kth_term(const vector<int> &f, const vector<int> &c, int k) {
    if (k < f.size()) return f[k];
    int n = c.size();
    if (n == 0) return 0;
    auto mul = [&](const vector<int> &p, const vector<int> &q) {
        vector<int> r(2 * n + 1);
        for (int i = 0; i <= n; ++i) for (int j = 0; j <= n; ++j) r[i + j] = (r[i + j] + p[i] * q[j]) % mod;
        for (int i = 2 * n; i > n; --i) for (int j = 0; j < n; ++j) r[i - 1 - j] = (r[i - 1 - j] + r[i] * c[j]) % mod;
        r.resize(n + 1);
        return r;
    };
    vector<int> res(n + 1), base(n + 1);
    res[0] = base[1] = 1;
    for (k++; k > 0; k /= 2) {
        if (k % 2 == 1) res = mul(res, base);
        base = mul(base, base);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) ans = (ans + res[i + 1] * f[i]) % mod;
    return ans;
}
