int mod_pow(int128 a, int e, const int mod) {
    int128 r = 1;
    while (e != 0) {
        if (e & 1) r = (r * a) % mod;
        a = (a * a) % mod;
        e >>= 1;
    }
    return r;
}

bool composite(int n, int a, int s, int d) {
    int128 x = mod_pow(a, d, n);
    if (x == 1 or x == n - 1) return false;
    for (int i = 1; i < s; ++i) {
        x = (x * x) % n;
        if (x == n - 1) return false;
        if (x == 1) return true;
    }
    return true;
}

bool prime(int n) {
    if (n <= 1) return false;
    static const int P[] = {2, 3, 5, 13, 19, 73, 193, 407521, 299210837};
    for (int p : P) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    int s = __builtin_ctzll(n - 1); 
    int d = (n - 1) >> s;
    static const int A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    for (int a : A) {
        if (composite(n, a, s, d)) return false;
    }
    return true;
}
