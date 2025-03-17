int power(int x, int y, int m) {
    if (y == 0) return 1;

    int p = power(x, y / 2, m);
    int n = (p * p) % m;

    if (y & 1) n = (n * x) % m;
    return n;
}
