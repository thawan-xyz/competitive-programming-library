// Pollard-Rho: fast integer factorization 
// Time: O(N^(1/4)) expected | Space: O(1)
// Note: finds a non-trivial divisor | use recursively to fully factor
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int f(int128 x, int c, const int mod) {
    return (x * x + c) % mod;
}

int pollard_rho(int n) {
    if ((n & 1) == 0) return 2;
    if (miller_rabin(n)) return n;
    int c = uniform_int_distribution<int>(1, n - 1)(rng);
    int x = 2, y = 2, g = 1, l = 1, p = 2, q = 1;
    while (g == 1) {
        y = x;
        int k = 0;
        while (k < l and g == 1) {
            p = x;
            for (int i = 1; i <= min<int>(128, l - k); ++i) {
                x = f(x, c, n);
                q = ((int128) q * abs(x - y)) % n;
            }
            g = gcd(q, n);
            k += 128;
        }
        l *= 2;
    }
    if (g == n) {
        do {
            p = f(p, c, n);
            g = gcd(abs(p - y), n);
        } while (g == 1);
    }
    if (g == n) return pollard_rho(n);
    return g;
}
