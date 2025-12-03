pair<int, int> chinese_remainder_theorem(array<int> &r, array<int> &m) {
    int n = m.size();

    int r1 = r[0];
    int m1 = m[0];
    for (int i = 1; i < n; ++i) {
        int r2 = r[i];
        int m2 = m[i];

        int g = gcd(m1, m2);
        if (r1 % g != r2 % g) return {-1, -1};

        auto [_, x, y] = extended_gcd(m1 / g, m2 / g);
        int l = lcm(m1, m2);

        int a = ((int128(r1) * (m2 / g) % l) * y) % l;
        int b = ((int128(r2) * (m1 / g) % l) * x) % l;

        r1 = (((a + b) % l) + l) % l;
        m1 = l;
    }
    return {r1, m1};
}
