int derangement(int n, int mod) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (dynamic[n] != -1) return dynamic[n];

    return dynamic[n] = (n - 1) * (derangement(n - 1, mod) + derangement(n - 2, mod)) % mod;
}
