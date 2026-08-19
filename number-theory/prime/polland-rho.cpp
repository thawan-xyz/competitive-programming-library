int f(int128 x, int c, const int mod) {
    return (x * x + c) % mod;
}

int polland_rho(int n) {
    if ((n & 1) == 0) return 2;
    if (miller_rabin(n)) return n;
    int x = 2, y = 2, c = 1, d = 1;
    while (d == 1) {
        x = f(x, c, n);
        y = f(f(y, c, n), c, n);
        d = gcd(abs(x - y), n);
        if (d == n) {
            uniform_int_distribution<int> rand_x(2, n - 2);
            uniform_int_distribution<int> rand_c(1, n - 1);
            x = rand_x(rng);
            y = x;
            c = rand_c(rng);
            d = 1;
        }
    }
    return d;
}
