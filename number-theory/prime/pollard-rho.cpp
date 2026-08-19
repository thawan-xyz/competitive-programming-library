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
    int x = 2, y = 2, c = 1, d = 1;
    while (d == 1) {
        x = f(x, c, n);
        y = f(f(y, c, n), c, n);
        d = gcd(abs(x - y), n);
        if (d == n) {
            x = uniform_int_distribution<int>(2, n - 2)(rng);
            y = x;
            c = uniform_int_distribution<int>(1, n - 1)(rng);
            d = 1;
        }
    }
    return d;
}
