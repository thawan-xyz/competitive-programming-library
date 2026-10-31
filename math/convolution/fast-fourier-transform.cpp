vector<complex<float>> roots = {{0, 1}};

void fft(vector<complex<float>> &f, bool inv) {
    int n = f.size();
    for (int k = roots.size(); k < n; k *= 2) {
        roots.resize(2 * k);
        float ang = acosl(-1) / k;
        for (int j = 0; j < k; ++j) roots[k + j] = {cos(ang * j), sin(ang * j)};
    }
    vector<int> rev(n);
    for (int i = 1; i < n; ++i) {
        rev[i] = (rev[i / 2] + (i & 1) * n) / 2;
        if (i < rev[i]) swap(f[i], f[rev[i]]);
    }
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; ++j) {
                complex<float> z = roots[k + j] * f[i + j + k];
                f[i + j + k] = f[i + j] - z;
                f[i + j] += z;
            }
        }
    }
    if (inv) {
        reverse(f.begin() + 1, f.end());
        for (complex<float> &x : f) x /= n;
    }
}

vector<int> convolution(const vector<int> &a, const vector<int> &b) {
    if (a.empty() or b.empty()) return {};
    int n = a.size() + b.size() - 1, m = 1;
    while (m < n) m *= 2;
    vector<complex<float>> f(m);
    for (int i = 0; i < a.size(); ++i) f[i].real(a[i]);
    for (int i = 0; i < b.size(); ++i) f[i].imag(b[i]);
    fft(f, false);
    for (complex<float> &x : f) x *= x;
    fft(f, true);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) c[i] = round(f[i].imag() / 2);
    return c;
}
