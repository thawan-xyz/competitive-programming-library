int inverse(int a, int m) {
    auto [g, x, y] = egcd(a, m);
    x %= m; if (x < 0) x += m;
    return x;
}
