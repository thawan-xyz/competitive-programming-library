bool composite(int n, int a, int s, int d) {
    int128 x = power(a, d, n);
    if (x == 1 or x == n - 1) return false;
    for (int i = 1; i < s; ++i) {
        x = (x * x) % n;
        if (x == n - 1) return false;
    }
    return true;
}

bool prime(int n) {
    if (n <= 1) return false;
    int s = 0, d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        s += 1;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (composite(n, a, s, d)) return false;
    }
    return true;
}
