void fwht(vector<int> &p, int sign) {
    int n = p.size();
    for (int l = 1; l < n; l <<= 1) {
        for (int i = 0; i < n; i += l << 1) {
            for (int j = 0; j < l; ++j) {
                int x = p[i + j];
                int y = p[(i + j) + l];
                p[i + j] = x + y;
                p[(i + j) + l] = x - y;
            }
        }
    }

    if (sign == -1) {
        for (int &z : p) {
            z /= n;
        }
    }
}

vector<int> xor_convolution(vector<int> &a, vector<int> &b) {
    int m = max(a.size(), b.size());
    int n = (m == 1) ? 1 : 1 << (32 - __builtin_clz(m - 1));

    a.resize(n), b.resize(n);
    fwht(a, 1), fwht(b, 1);

    vector<int> c(n);
    for (int i = 0; i < n; ++i) c[i] = a[i] * b[i];
    fwht(c, -1);
    return c;
}
