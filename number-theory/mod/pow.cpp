int pow(int b, int e, int mod) {
    int a = 1;

    while (e) {
        if (e & 1) a *= b, a %= mod;

        b *= b, b %= mod;
        e >>= 1;
    }
    return a;
}
