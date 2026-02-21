list<int> sum_over_subsets(int n, list<int> f) {
    int full = (1 << n) - 1;
    for (int i = 0; i < n; ++i) {
        int bit = 1 << i;
        for (int mask = 0; mask <= full; ++mask) if (mask & bit) {
            f[mask] += f[mask ^ bit];
        }
    }
    return f;
}
