void permute(list<complex<float>> &p, list<int> &order) {
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        int j = order[i];
        if (i < j) swap(p[i], p[j]);
    }
}

void fast_fourier_transform(list<complex<float>> &p, int sign, list<int> &order) {
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

list<int> convolution(list<int> &a, list<int> &b) {
    int n = a.size() + b.size() - 1;
    int m = (n == 1) ? 1 : 1 << (32 - __builtin_clz(n - 1));
    int l = __builtin_ctz(m);

    list<int> order(m);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < l; ++j) {
            if (i & (1 << j)) {
                order[i] |= 1 << (l - (j + 1));
            }
        }
    }

    list<complex<float>> x(a.begin(), a.end()); x.resize(m);
    list<complex<float>> y(b.begin(), b.end()); y.resize(m);
    fast_fourier_transform(x, 1, order);
    fast_fourier_transform(y, 1, order);

    list<complex<float>> z(m);
    for (int i = 0; i < m; ++i) z[i] = x[i] * y[i];
    fast_fourier_transform(z, -1, order);

    list<int> c(n);
    for (int i = 0; i < n; ++i) c[i] = round(z[i].real());
    return c;
}
