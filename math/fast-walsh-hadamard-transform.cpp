void fast_walsh_hadamard_transform(array<int> &p, int sign) {
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
    if (sign == -1) for (int &z : p) z /= n;
}

array<int> xor_convolution(array<int> &a, array<int> &b) {
    int m = max(a.size(), b.size());
    int n = (m == 1) ? 1 : 1 << (32 - __builtin_clz(m - 1));

    a.resize(n), fast_walsh_hadamard_transform(a, 1);
    b.resize(n), fast_walsh_hadamard_transform(b, 1);

    array<int> c(n);
    for (int i = 0; i < n; ++i) c[i] = a[i] * b[i];
    fast_walsh_hadamard_transform(c, -1);
    return c;
}
