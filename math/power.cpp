int power(int base, int exponent, int mod) {
    int result = 1;
    base %= mod;

    while (exponent) {
        if (exponent & 1) result = (result * base) % mod;

        base = (base * base) % mod;
        exponent >>= 1;
    }
    return result;
}
