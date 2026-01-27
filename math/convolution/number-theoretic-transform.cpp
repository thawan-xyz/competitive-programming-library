const int mod = 998244353, g = 3;

void permute(list<int> &p, list<int> &order) {
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int j = order[i];
        if (i < j) swap(p[i], p[j]);
    }
}

void number_theoretic_transform(list<int> &p, int sign, list<int> &order, int inv) {
    int n = p.size();
    permute(p, order);

    for (int l = 1; l < n; l <<= 1) {
        int step = power(g, (mod - 1) / (l << 1));
        if (sign == -1) step = power(step, mod - 2);

        for (int i = 0; i < n; i += l << 1) {
            int w = 1;
            for (int j = 0; j < l; ++j) {
                int x = p[i + j];
                int y = (w * p[(i + j) + l]) % mod;
                p[i + j] = (x + y) % mod;
                p[(i + j) + l] = ((x - y) + mod) % mod;
                w = (w * step) % mod;
            }
        }
    }

    if (sign == -1) for (int &i : p) i = (i * inv) % mod;
}

list<int> convolution(list<int> &a, list<int> &b) {
    int n = a.size() + b.size() - 1;
    int m = (n == 1) ? 1 : 1 << (32 - __builtin_clz(n - 1));
    int l = __builtin_ctz(m);

    list<int> order(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < l; ++j) {
            if (i & (1 << j)) {
                order[i] |= 1 << (l - (j + 1));
            }
        }
    }

    int inv = power(m, mod - 2);
    a.resize(m); number_theoretic_transform(a, 1, order, inv);
    b.resize(m); number_theoretic_transform(b, 1, order, inv);

    list<int> c(m);
    for (int i = 0; i < m; ++i) c[i] = (a[i] * b[i]) % mod;
    number_theoretic_transform(c, -1, order, inv);
    c.resize(n);

    return c;
}
