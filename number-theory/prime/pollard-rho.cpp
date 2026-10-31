int pollard_rho(int n) {
    if (n % 2 == 0) return 2;
    for (int c = 1;; ++c) {
        auto f = [&](int x) { return (int) (((int128) x * x + c) % n); };
        int x = 2, y = 2, q = 1, g = 1;
        for (int r = 1; g == 1; r *= 2) {
            x = y;
            for (int i = 0; i < r and g == 1; ++i) {
                y = f(y);
                q = (int128) q * abs(x - y) % n;
                if (i % 128 == 127 or i == r - 1) g = gcd(q, n);
            }
        }
        if (g != n) return g;
    }
}

vector<int> factorize(int n) {
    vector<int> primes, todo = {n};
    while (todo.size()) {
        int m = todo.back(); todo.pop_back();
        if (m == 1) continue;
        if (miller_rabin(m)) {
            primes.push_back(m);
        } else {
            int d = pollard_rho(m);
            todo.push_back(d), todo.push_back(m / d);
        }
    }
    sort(primes.begin(), primes.end());
    return primes;
}
