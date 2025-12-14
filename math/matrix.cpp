using matrix = list<list<int>>;

matrix product(matrix &a, matrix &b) {
    int n = a.size();
    int m = b[0].size();
    int s = a[0].size();

    matrix c(n, list<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < s; ++k) {
                c[i][j] += (a[i][k] * b[k][j]) % mod;
                c[i][j] %= mod;
            }
        }
    }
    return c;
}

matrix pow(matrix &b, int e) {
    int n = b.size();

    matrix a(n, list<int>(n));
    for (int i = 0; i < n; ++i) a[i][i] = 1;

    while (e) {
        if (e & 1) a = product(a, b);

        b = product(b, b);
        e >>= 1;
    }
    return a;
}
