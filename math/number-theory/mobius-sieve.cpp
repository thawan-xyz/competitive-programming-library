array<int> mobius(int n) {
    array<int> µ(n + 1);
    for (int i = 1; i <= n; ++i) {
        µ[i] = 1;
    }

    array<bool> c(n + 1);
    for (int i = 2; i <= n; ++i) if (not c[i]) {
        for (int j = i; j <= n; j += i) {
            µ[j] *= -1;
            c[j] = true;
        }
        for (int j = i * i; j <= n; j += i * i) {
            µ[j] = 0;
        }
    }
    return µ;
}
