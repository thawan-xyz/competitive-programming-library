int power(int x, int y, int m) {
    int n = 1;
    x %= m;
    while (y > 0) {
        if (y & 1) n = (n * x) % m;
        x = (x * x) % m, y >>= 1;
    }
    return n;
}
