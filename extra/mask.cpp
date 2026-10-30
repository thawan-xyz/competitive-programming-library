void submasks(int mask) {
    for (int sub = mask; sub > 0; sub = mask & (sub - 1)) {
        process(sub);
    }
    process(0);
}

vector<int> sum_over_subsets(int n, vector<int> f) {
    for (int i = 0; i < n; ++i) {
        int bit = 1 << i;
        for (int mask = 0; mask < (1 << n); ++mask) if (mask & bit) {
            f[mask] += f[mask ^ bit];
        }
    }
    return f;
}

vector<int> sum_over_supersets(int n, vector<int> f) {
    for (int i = 0; i < n; ++i) {
        int bit = 1 << i;
        for (int mask = 0; mask < (1 << n); ++mask) if (not (mask & bit)) {
            f[mask] += f[mask | bit];
        }
    }
    return f;
}
