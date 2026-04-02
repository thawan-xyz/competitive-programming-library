vector<int> linear_sieve(int n) {
    vector<int> p, spf(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            p.push_back(i);
        }
        for (int j : p) {
            if (j > spf[i] or i * j > n) break;
            spf[i * j] = j;
        }
    }
    return p;
}
