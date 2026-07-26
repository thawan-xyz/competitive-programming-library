const float pi = acos(-1);

vector<complex<float>> roots(int half, float ang) {
    vector<complex<float>> w(half);
    w[0] = {1, 0};
    for (int i = 1; i < half; i *= 2) {
        complex<float> step(cos(ang * i), sin(ang * i));
        for (int j = 0; j < i; ++j) {
            w[i + j] = w[j] * step;
        }
    }
    return w;
}

void fft(vector<complex<float>> &p, bool inv) {
    int n = p.size();
    if (not inv) {
        for (int len = n; len >= 2; len /= 2) {
            int half = len / 2;
            float ang = 2 * pi / len;
            auto w = roots(half, ang);
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < half; ++j) {
                    auto x = p[i + j];
                    auto y = p[i + j + half];
                    p[i + j] = x + y;
                    p[i + j + half] = (x - y) * w[j];
                }
            }
        }
    } else {
        for (int len = 2; len <= n; len *= 2) {
            int half = len / 2;
            float ang = -2 * pi / len;
            auto w = roots(half, ang);
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < half; ++j) {
                    auto x = p[i + j];
                    auto y = p[i + j + half] * w[j];
                    p[i + j] = x + y;
                    p[i + j + half] = x - y;
                }
            }
        }
        for (auto &x : p) x /= n;
    }
}

vector<int> convolution(vector<int> &a, vector<int> &b) {
    int n = a.size() + b.size() - 1;
    int m = 1;
    while (m < n) m *= 2;

    vector<complex<float>> fa(a.begin(), a.end());
    vector<complex<float>> fb(b.begin(), b.end());
    fa.resize(m);
    fb.resize(m);
    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < m; ++i) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> c(n);
    for (int i = 0; i < n; ++i) c[i] = round(fa[i].real());
    return c;
}
