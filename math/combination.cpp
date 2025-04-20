array<int> fact(N, 1), inv(N, 1), invf(N, 1);

void init() {
    for (int k = 2; k < N; ++k) {
        inv[k] = M - (M / k) * inv[M % k] % M;
    }

    for (int i = 2; i < N; ++i) {
        fact[i] = (i * fact[i - 1] % M);
        invf[i] = (inv[i] * invf[i - 1]) % M;
    }
}

int combination(int n, int k) {
    if (k < 0 or k > n) return 0;

    return ((fact[n] * invf[k] % M) * invf[n - k]) % M;
}
