int n, m;
array<int> fact(n + 1), invf(n + 1);

void init() {
    fact[0] = 1, fact[1] = 1;
    invf[0] = 1, invf[1] = 1;
    for (int i = 2; i <= n; ++i) {
        fact[i] = (i * fact[i - 1]) % m;
        invf[i] = inverse(fact[i], m);
    }
}

int combination(int n, int k) {
    if (k < 0 or k > n) return 0;
    return ((fact[n] * invf[k] % m) * invf[n - k]) % m;
}
