using matrix = array<array<int>>;

matrix identity(int n) {
    matrix identity(n, array<int>(n));

    for (int i = 0; i < n; ++i) {
        identity[i][i] = 1;
    }
    return identity;
}

matrix multiply(matrix a, matrix b, int mod) {
    int n = a.size();
    matrix result(n, array<int>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += (a[i][k] * b[k][j]) % mod;
                if (result[i][j] >= mod) result[i][j] -= mod;
            }
        }
    }
    return result;
}

matrix power(matrix base, int exp, int mod) {
    int n = base.size();
    matrix result = identity(n);

    while (exp > 0) {
        if (exp & 1) {
            result = multiply(result, base, mod);
        }
        base = multiply(base, base, mod);
        exp >>= 1;
    }
    return result;
}
