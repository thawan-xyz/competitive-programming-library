bool miller_rabin(int n) {
    if (n < 2) return false;
    for (int p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }
    int s = __builtin_ctzll(n - 1), d = (n - 1) >> s;
    for (int a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (a % n == 0) continue;
        int128 x = 1, b = a % n;
        for (int e = d; e > 0; e /= 2) {
            if (e & 1) x = x * b % n;
            b = b * b % n
        }
        if (x == 1) continue;
        for (int i = 1; i < s and x != n - 1; ++i) x = x * x % n;
        if (x != n - 1) return false;
    }
    return true;
}
