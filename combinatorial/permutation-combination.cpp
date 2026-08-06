int P(int n, int k) {
    if (k < 0 or n < k) return 0;
    return fact[n] * invf[n - k] % mod;
}

int C(int n, int k) {
    if (k < 0 or n < k) return 0;
    return P(n, k) * invf[k] % mod;
}
