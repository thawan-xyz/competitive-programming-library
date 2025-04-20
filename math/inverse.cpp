int inverse(int n, int mod) {
    auto [g, x, y] = egcd(n, mod);
    
    return ((x % mod) + mod) % mod;
}
