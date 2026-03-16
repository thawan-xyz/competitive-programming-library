void factorial() {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = i * fact[i - 1] % mod;
    invf[n] = mod_pow(fact[n], mod - 2);
    for (int i = n - 1; i >= 0; --i) invf[i] = (i + 1) * invf[i + 1] % mod;
}
