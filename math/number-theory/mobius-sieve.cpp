array<int> mobius_sieve(int n) {
    array<int> mu(n + 1);
    for (int i = 1; i <= n; ++i) {
        mu[i] = 1;
    }

    array<bool> c(n + 1);
    for (int i = 2; i <= n; ++i) if (not c[i]) {
        for (int j = i; j <= n; j += i) {
            mu[j] *= -1;
            c[j] = true;
        }
        for (int j = i * i; j <= n; j += i * i) {
            mu[j] = 0;
        }
    }
    return mu;
}
