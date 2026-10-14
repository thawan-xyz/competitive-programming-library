const float pi = acos(-1);
vector<complex<float>> root, inv_root;

void roots(int n) {
    if (n <= 2 * root.size()) return;

    root.resize(n / 2);
    inv_root.resize(n / 2);

    root[0] = {1, 0};
    inv_root[0] = {1, 0};

    float ang = 2 * pi / n;
    int half = n / 2;
    for (int i = 1; i < half; i *= 2) {
        complex<float> step(cos(ang * i), sin(ang * i));
        for (int j = 0; j < i; ++j) {
            root[i + j] = root[j] * step;
        }
    }
    for (int i = 1; i < half; ++i) {
        inv_root[i] = conj(root[i]);
    }
}

void fft(vector<complex<float>> &p, bool inv) {
    int n = p.size();
    roots(n);
    if (not inv) {
        for (int len = n; len >= 2; len /= 2) {
            int half = len / 2;
            int step = 2 * root.size() / len;
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < half; ++j) {
                    auto w = root[step * j];
                    auto x = p[i + j];
                    auto y = p[i + j + half];
                    p[i + j] = x + y;
                    p[i + j + half] = (x - y) * w;
                }
            }
        }
    } else {
        for (int len = 2; len <= n; len *= 2) {
            int half = len / 2;
            int step = 2 * root.size() / len;
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < half; ++j) {
                    auto w = inv_root[step * j];
                    auto x = p[i + j];
                    auto y = p[i + j + half] * w;
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
