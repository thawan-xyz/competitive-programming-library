array<int> mobius(int n) {
    array<int> µ(n + 1, 1);
    array<bool> p(n + 1, true);
    for (int i = 2; i <= n; ++i) if (p[i]) {
        µ[i] = -1;
        for (int j = 2 * i; j <= n; j += i) {
            µ[j] *= -1;
            p[j] = false;
        }
        for (int j = i * i; j <= n; j += i * i) {
            µ[j] = 0;
        }
    }
    return µ;
}

array<int> inclusion_exclusion(int n, array<int> &c) {
    array<int> µ = mobius(n);

    array<int> f(n + 1);
    for (int i = 1; i <= n; ++i) if (µ[i] != 0) {
        for (int j = i; j <= n; j += i) {
            f[j] += µ[i] * c[i];
        }
    }
    return f;
}
