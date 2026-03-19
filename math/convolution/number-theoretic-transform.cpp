void ntt(vector<int> &p, int g, int mod, bool inv) {
    int n = p.size();
    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (j & bit) j ^= bit, bit >>= 1;
        j ^= bit;
        if (i < j) swap(p[i], p[j]);
    }

    for (int len = 2; len <= n; len *= 2) {
        int half = len / 2;
        int ang = mod_pow(g, (mod - 1) / len, mod);
        if (inv) ang = mod_pow(ang, mod - 2, mod);
        for (int i = 0; i < n; i += len) {
            for (int j = 0, w = 1; j < half; ++j, w = (w * ang) % mod) {
                int x = p[i + j];
                int y = (p[(i + j) + half] * w) % mod;
                p[i + j] = (x + y) % mod;
                p[(i + j) + half] = ((x - y) + mod) % mod;
            }
        }
    }

    if (inv) {
        int inv_n = mod_pow(n, mod - 2, mod);
        for (int &x : p) x = (x * inv_n) % mod;
    }
}

vector<int> convolution(vector<int> a, vector<int> b, int g = 3, int mod = 998244353) {
    int n = a.size() + b.size() - 1, m = 1;
    while (m < n) m *= 2;

    a.resize(m), b.resize(m);
    ntt(a, g, mod, false), ntt(b, g, mod, false);
    for (int i = 0; i < m; ++i) a[i] = (a[i] * b[i]) % mod;

    ntt(a, g, mod, true);
    a.resize(n);
    return a;
}
