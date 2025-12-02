pair<int, array<int>> multi_extended_gcd(array<int> &a) {
    int n = a.size(), g = a[0];
    array<int> c(n, 1), h(n, 1);
    for (int i = 1; i < n; ++i) {
        auto [_, x, y] = extended_gcd(g, a[i]);
        g = _;
        h[i - 1] = x;
        c[i] = y;
    }
    for (int i = n - 1; i >= 0; --i) {
        if (i < n - 1) h[i] *= h[i + 1];
        c[i] *= h[i];
    }
    return {g, c};
}
