int reverse(int i, int log) {
    int k = 0;
    for (int j = 0; j < log; ++j) {
        if (i & (1 << j)) {
            k |= 1 << (log - (j + 1));
        }
    }
    return k;
}

void FFT(array<complex<float>> &p, bool inverse) {
    int n = p.size();
    int log = log2(n);
    for (int i = 0; i < n; ++i) {
        int j = reverse(i, log);
        if (i < j) {
            swap(p[i], p[j]);
        }
    }

    for (int l = 1; l < n; l <<= 1) {
        float ang = M_PI / l * (inverse ? -1 : 1);
        complex<float> step(cos(ang), sin(ang));

        for (int i = 0; i < n; i += l << 1) {
            complex<float> w(1, 0);
            for (int j = 0; j < l; ++j) {
                complex<float> x = p[i + j];
                complex<float> y = w * p[(i + j) + l];
                p[i + j] = x + y;
                p[(i + j) + l] = x - y;
                w *= step;
            }
        }
    }

    if (inverse) {
        for (complex<float> &z : p) {
            z /= n;
        }
    }
}

array<int> multiply(array<int> &a, array<int> &b) {
    int n = a.size() + b.size() - 1;
    int m = pow2(n);

    array<complex<float>> x(a.begin(), a.end());
    array<complex<float>> y(b.begin(), b.end());
    x.resize(m);
    y.resize(m);

    FFT(x, false);
    FFT(y, false);

    array<complex<float>> z(m);
    for (int i = 0; i < m; ++i) {
        z[i] = x[i] * y[i];
    }

    FFT(z, true);

    array<int> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = round(z[i].real());
    }
    return c;
}
