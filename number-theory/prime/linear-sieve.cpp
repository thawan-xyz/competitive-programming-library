vector<int> linear_sieve(int n) {
    vector<int> p, lp(n + 1);
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            p.push_back(i);
        }
        for (int j : p) {
            if (j > lp[i] or i * j > n) break;
            lp[i * j] = j;
        }
    }
    return p;
}
