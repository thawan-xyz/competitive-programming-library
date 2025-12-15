array<int> euler_totient(int n) {
    array<int> φ(n + 1);
    for (int i = 1; i <= n; ++i) {
        φ[i] = i;
    }

    for (int i = 2; i <= n; ++i) if (φ[i] == i) {
        for (int j = i; j <= n; j += i) {
            φ[j] -= φ[j] / i;
        }
    }
    return φ;
}
