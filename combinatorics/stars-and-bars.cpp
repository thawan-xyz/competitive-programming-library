int stars_and_bars(int n, int k) {
    if (n < 0 or k < 0) return 0;
    if (k == 0) return n == 0;
    return nCk(n + k - 1, k - 1);
}
