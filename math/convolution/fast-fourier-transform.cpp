const float pi = acos(-1);

void fft(vector<complex<float>> &p, int sign) {
    int n = p.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        while (j & bit) j ^= bit, bit >>= 1;
        j ^= bit;
        if (i < j) swap(p[i], p[j]);
    }

    for (int len = 2; len <= n; len *= 2) {
        int half = len / 2;
        float ang = sign * (2 * pi / len);
        complex<float> step(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            complex<float> w(1, 0);
            for (int j = 0; j < half; ++j) {
                auto x = p[i + j];
                auto y = w * p[(i + j) + half];
                p[i + j] = x + y;
                p[(i + j) + half] = x - y;
                w *= step;
            }
        }
    }

    if (sign == -1) {
        for (complex<float> &x : p) x /= n;
    }
}

vector<int> convolution(vector<int> &a, vector<int> &b) {
    int n = a.size() + b.size() - 1, m = 1;
    while (m < n) m *= 2;

    vector<complex<float>> fa(a.begin(), a.end());
    vector<complex<float>> fb(b.begin(), b.end());
    fa.resize(m);
    fb.resize(m);

    fft(fa, +1);
    fft(fb, +1);

    for (int i = 0; i < m; ++i) fa[i] *= fb[i];
    fft(fa, -1);

    vector<int> c(n);
    for (int i = 0; i < n; ++i) c[i] = round(fa[i].real());
    return c;
}
