pair<int, int> chinese_remainder_theorem(array<int> &r, array<int> &mod) {
    int n = mod.size();

    int i = r[0];
    int s = mod[0];
    for (int k = 1; k < n; ++k) {
        int j = r[k];
        int t = mod[k];

        int g = gcd(s, t);
        if (i % g != j % g) return {-1, -1};

        auto [_, x, y] = extended_gcd(s / g, t / g);
        int l = lcm(s, t);

        int a = ((int128(i) * (t / g) % l) * y) % l;
        int b = ((int128(j) * (s / g) % l) * x) % l;

        i = (((a + b) % l) + l) % l;
        s = l;
    }
    return {i, s};
}
