int catalan(int n) {
    if (n < 0) return 0;
    return (fact[n] * invf[n + 1] % mod) * nCk(2 * n, n) % mod;
}
