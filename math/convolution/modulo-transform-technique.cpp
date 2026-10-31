vector<int> mtt(const vector<int> &a, const vector<int> &b, int mod) {
    const int p = 998244353, q = 167772161, r = 469762049;
    vector<int> x = convolution<p>(a, b), y = convolution<q>(a, b), z = convolution<r>(a, b);
    int p_inv = mod_pow(p, q - 2, q), pq_inv = mod_pow(p * q % r, r - 2, r);
    for (int i = 0; i < x.size(); ++i) {
        int s = ((y[i] - x[i]) % q + q) % q * p_inv % q;
        int t = ((z[i] - x[i] - p * s) % r + r) % r * pq_inv % r;
        x[i] = (x[i] + p * s + p * q % mod * t) % mod;
    }
    return x;
}
