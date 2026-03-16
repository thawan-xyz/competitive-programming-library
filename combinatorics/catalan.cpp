int catalan(int n) {
    if (n < 0) return 0;
    return ((nCk(2 * n, n) - nCk(2 * n, n + 1)) % mod + mod) % mod;
}
