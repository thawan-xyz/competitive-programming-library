int lucas(int n, int k) {
    if (k == 0 or k == n) return 1;
    if (k > n) return 0;
    return (lucas(n / mod, k / mod) * nCk(n % mod, k % mod)) % mod;
}
