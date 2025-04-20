int power(int base, int exp, int mod) {
    int result = 1;
    base %= mod;

    while (exp > 0) {
        if (exp & 1) {
            result *= base;
            result %= mod;
        }
        base *= base;
        base %= mod;
        exp >>= 1;
    }
    return result;
}
