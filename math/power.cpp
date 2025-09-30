int power(int base, int exponent) {
    int result = 1;
    base %= mod;

    while (exponent) {
        if (exponent & 1) {
            result *= base;
            result %= mod;
        }

        base *= base;
        base %= mod;
        exponent >>= 1;
    }
    return result;
}
