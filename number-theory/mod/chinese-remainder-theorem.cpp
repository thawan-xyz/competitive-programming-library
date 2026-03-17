int chinese_remainder_theorem(const vector<int> &rem, const vector<int> &mod) {
    int r = rem[0], m = mod[0];
    for (int i = 1; i < rem.size(); ++i) {
        int g = gcd(m, mod[i]), h = mod[i] / g;
        if ((rem[i] - r) % g != 0) return -1;

        auto [_, a, b] = extended_gcd(m / g, h);

        r += m * ((((int128(rem[i] - r) / g) * a) % h + h) % h);
        m *= h;
    }
    return r;
}
