int128 chinese_remainder_theorem(const vector<int> &rem, const vector<int> &mod) {
    int128 r = rem[0], m = mod[0];
    for (int i = 1; i < rem.size(); ++i) {
        int g = gcd(static_cast<int>(m % mod[i]), mod[i]), h = mod[i] / g;
        if ((rem[i] - r) % g != 0) return -1;

        auto [x, _] = extended_gcd(static_cast<int>(m / g % h), h);

        r += m * (((((rem[i] - r) / g) * x) % h + h) % h);
        m *= h;
    }
    return r;
}
