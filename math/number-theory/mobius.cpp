int mobius(int n) {
    int mu = 1;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
        n /= i;
        if (n % i == 0) return 0;
        mu *= -1;
    }
    if (n > 1) mu *= -1;
    return mu;
}

array<int> mobius_sieve(int n) {
    array<int> mu(n + 1, 1);
    array<bool> p(n + 1, true);
    for (int i = 2; i <= n; ++i) if (p[i]) {
        mu[i] = -1;
        for (int j = 2 * i; j <= n; j += i) {
            mu[j] *= -1;
            p[j] = false;
        }
        for (int j = i * i; j <= n; j += i * i) {
            mu[j] = 0;
        }
    }
    return mu;
}

array<int> inclusion_exclusion(int n, array<int> &c) {
    array<int> mu = mobius_sieve(n);

    array<int> f(n + 1);
    for (int i = 1; i <= n; ++i) if (mu[i] != 0) {
        for (int j = i; j <= n; j += i) {
            f[j] += mu[i] * c[j / i];
        }
    }
    return f;
}
