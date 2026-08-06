int mod_pow(int a, int e, const int mod) {
    int r = 1;
    while (e != 0) {
        if (e & 1) r = (r * a) % mod;
        a = (a * a) % mod;
        e >>= 1;
    }
    return r;
}
