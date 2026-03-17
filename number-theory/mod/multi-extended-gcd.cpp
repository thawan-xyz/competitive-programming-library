vector<int> multi_extended_gcd(vector<int> &a) {
    int n = a.size(), g = a[0];
    vector<int> c(n, 1), h(n - 1);

    for (int i = 1; i < n; ++i) {
        auto [x, y] = extended_gcd(g, a[i]);
        g = gcd(g, a[i]);
        h[i - 1] = x;
        c[i] = y;
    }

    int p = 1;
    for (int i = n - 1; i > 0; --i) {
        c[i] *= p;
        p *= h[i - 1];
    }
    c[0] *= p;
    return c;
}
