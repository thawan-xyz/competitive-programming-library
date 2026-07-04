int catalan(int l, int r) {
    if ((l < 0 or r < 0) or l < r) return 0;
    return (C(l + r, l) - C(l + r, l + 1) + mod) % mod;
}
