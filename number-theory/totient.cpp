int totient(int n) {
    int phi = n;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
        phi -= phi / i;
        while (n % i == 0) n /= i;
    }
    if (n > 1) phi -= phi / n;
    return phi;
}

array<int> totient_sieve(int n) {
    array<int> phi(n + 1);
    for (int i = 1; i <= n; ++i) {
        phi[i] = i;
    }
    for (int i = 2; i <= n; ++i) if (phi[i] == i) {
        for (int j = i; j <= n; j += i) {
            phi[j] -= phi[j] / i;
        }
    }
    return phi;
}
