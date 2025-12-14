int pow(int b, int e) {
    int a = 1;

    while (e) {
        if (e & 1) a = (a * b) % mod;

        b = (b * b) % mod;
        e >>= 1;
    }
    return a;
}
