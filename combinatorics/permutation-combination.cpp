int nPk(int n, int k) {
    if (k < 0 or n < k) return 0;
    return fact[n] * invf[n - k] % mod;
}

int nCk(int n, int k) {
    if (k < 0 or n < k) return 0;
    return nPk(n, k) * invf[k] % mod;
}
