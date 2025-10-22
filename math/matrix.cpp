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

matrix power(matrix &base, int exponent) {
    int n = base.size();

    matrix result(n, list<int>(n));
    for (int i = 0; i < n; ++i) result[i][i] = 1;

    while (exponent) {
        if (exponent & 1) result = product(base, result);

        base = product(base, base);
        exponent >>= 1;
    }
    return result;
}
