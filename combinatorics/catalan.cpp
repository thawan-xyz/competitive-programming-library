int catalan(int l, int r) {
    if (l < 0 or l < r) return 0;
    return ((nCk(l + r, l) - nCk(l + r, l + 1)) % mod + mod) % mod;
}
