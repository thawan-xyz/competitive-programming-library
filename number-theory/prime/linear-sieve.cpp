list<int> linear_sieve(int n) {
    list<int> low(n + 1);
    list<int> primes;
    for (int i = 2; i <= n; ++i) {
        if (low[i] == 0) {
            low[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > low[i] or p * i > n) break;
            low[p * i] = p;
        }
    }
    return primes;
}
