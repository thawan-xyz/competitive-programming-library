vector<int> roots(int half, int ang, int mod) {
    vector<int> w(half);
    w[0] = 1;
    for (int i = 1; i < half; ++i) w[i] = (ang * w[i - 1]) % mod;
    return w;
}

void ntt(vector<int> &p, bool inv, int g, int mod) {
    int n = p.size();
    if (not inv) {
        for (int len = n; len >= 2; len /= 2) {
            int half = len / 2;
            int ang = mpow(g, (mod - 1) / len, mod);
            vector<int> w = roots(half, ang, mod);
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < half; ++j) {
                    int x = p[i + j];
                    int y = p[i + j + half];
                    p[i + j] = (x + y) % mod;
                    p[i + j + half] = (((x - y + mod) % mod) * w[j]) % mod;
                }
            }
        }
    } else {
        for (int len = 2; len <= n; len *= 2) {
            int half = len / 2;
            int ang = mpow(g, (mod - 1) / len, mod);
            ang = mpow(ang, mod - 2, mod);
            vector<int> w = roots(half, ang, mod);
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < half; ++j) {
                    int x = p[i + j];
                    int y = (p[i + j + half] * w[j]) % mod;
                    p[i + j] = (x + y) % mod;
                    p[i + j + half] = (x - y + mod) % mod;
                }
            }
        }
        int inv_n = mpow(n, mod - 2, mod);
        for (int &x : p) x = (x * inv_n) % mod;
    }
}

vector<int> convolution(vector<int> a, vector<int> b, int g = 3, int mod = 998244353) {
    int n = a.size() + b.size() - 1;
    int m = 1;
    while (m < n) m *= 2;

    a.resize(m);
    b.resize(m);
    ntt(a, false, g, mod);
    ntt(b, false, g, mod);

    for (int i = 0; i < m; ++i) a[i] = (a[i] * b[i]) % mod;
    ntt(a, true, g, mod);
    a.resize(n);

    return a;
}

vector<int> mtt(vector<int> &a, vector<int> &b, int mod) {
    vector<int> mods = {998244353, 1004535809, 469762049};

    vector<int> c1 = convolution(a, b, 3, mods[0]);
    vector<int> c2 = convolution(a, b, 3, mods[1]);
    vector<int> c3 = convolution(a, b, 3, mods[2]);

    int n = c1.size();
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        vector<int> rems = {c1[i], c2[i], c3[i]};
        int128 x = chinese_remainder_theorem(rems, mods);
        c[i] = x % mod;
    }
    return c;
}
