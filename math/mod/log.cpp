int log(int a, int b, int mod) {
    if (a == 0) {
        if (b == 0) return 1;
        return -1;
    }

    int k = 1, h = 0;
    for (int g = gcd(a, mod); g != 1; g = gcd(a, mod), ++h) {
        if (k == b) return h;
        if (b % g) return -1;

        b /= g, mod /= g;
        k = (k * (a / g)) % mod;
    }

    int n = ceil(sqrt(mod)), s = 1;
    for (int i = 1; i <= n; ++i) {
        s = (s * a) % mod;
    }

    map<int, int> f;
    for (int q = 0; q <= n; ++q) {
        f[b] = q;
        b = (b * a) % mod;
    }

    a = (k * s) % mod;
    for (int p = 1; p <= n; ++p) {
        if (f.contains(a)) {
            return (n * p - f[a]) + h;
        }
         a = (a * s) % mod;
    }
    return -1;
}
