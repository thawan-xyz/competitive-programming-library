array<int> build(int n) {
    array<int> order(n);
    int l = __builtin_ctzll(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l; ++j) {
            if (i & (1 << j)) {
                order[i] |= 1 << (l - (j + 1));
            }
        }
    }
    return order;
}

void permute(array<complex<float>> &p, array<int> &order) {
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int j = order[i];
        if (i < j) swap(p[i], p[j]);
    }
}

void fast_fourier_transform(array<complex<float>> &p, int sign, array<int> &order) {
    int n = p.size();
    permute(p, order);

    for (int l = 1; l < n; l <<= 1) {
        float a = sign * M_PI / l;
        complex<float> step(cos(a), sin(a));

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

    if (sign == -1) for (complex<float> &c : p) c /= n;
}

array<int> convolution(array<int> &a, array<int> &b) {
    int n = a.size() + b.size() - 1;
    int m = 1 << (64 - __builtin_clzll(n - 1));
    array<int> order = build(m);

    array<complex<float>> x(a.begin(), a.end()); x.resize(m);
    array<complex<float>> y(b.begin(), b.end()); y.resize(m);
    fast_fourier_transform(x, 1, order);
    fast_fourier_transform(y, 1, order);

    array<complex<float>> z(m);
    for (int i = 0; i < m; ++i) z[i] = x[i] * y[i];
    fast_fourier_transform(z, -1, order);

    array<int> c(n);
    for (int i = 0; i < n; ++i) c[i] = round(z[i].real());
    return c;
}
