vector<int> roots = {0, 1};

template<int mod = 998244353> void ntt(vector<int> &f, bool inv) {
    static vector<int> roots = {0, 1};
    int n = f.size();
    for (int k = roots.size(); k < n; k *= 2) {
        roots.resize(2 * k);
        int w = mod_pow(3, (mod - 1) / (2 * k), mod);
        for (int j = 0; j < k; ++j) roots[k + j] = (j == 0) ? 1 : roots[k + j - 1] * w % mod;
    }
    vector<int> rev(n);
    for (int i = 1; i < n; ++i) {
        rev[i] = (rev[i / 2] + (i & 1) * n) / 2;
        if (i < rev[i]) swap(f[i], f[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; ++j) {
                int x = f[i + j], z = roots[k + j] * f[i + j + k] % mod;
                f[i + j] = (x + z < mod) ? x + z : x + z - mod;
                f[i + j + k] = (x - z >= 0) ? x - z : x - z + mod;
            }
        }
    }
    if (inv) {
        reverse(f.begin() + 1, f.end());
        int inv_n = mod_pow(n, mod - 2, mod);
        for (int &x : f) x = x * inv_n % mod;
    }
}

template<int mod = 998244353> vector<int> convolution(vector<int> a, vector<int> b) {
    if (a.empty() or b.empty()) return {};
    int n = a.size() + b.size() - 1, m = 1;
    while (m < n) m *= 2;
    a.resize(m), b.resize(m);
    for (int i = 0; i < m; ++i) a[i] %= mod, b[i] %= mod;
    ntt<mod>(a, false), ntt<mod>(b, false);
    for (int i = 0; i < m; ++i) a[i] = a[i] * b[i] % mod;
    ntt<mod>(a, true);
    a.resize(n);
    return a;
}
