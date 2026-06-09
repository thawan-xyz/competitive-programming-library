using matrix = vector<vector<int>>;

matrix operator*(const matrix &a, const matrix &b) {
    int n = a.size();
    int m = b[0].size();
    int h = b.size();
    matrix r(n, vector<int>(m, inf));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < h; ++k) {
            for (int j = 0; j < m; ++j) {
                r[i][j] = min(r[i][j], a[i][k] + b[k][j]);
            }
        }
    }
    return r;
}

matrix operator^(matrix a, int b) {
    int n = a.size();
    matrix r(n, vector<int>(n, inf));
    for (int i = 0; i < n; ++i) r[i][i] = 0;
    while (b != 0) {
        if (b & 1) r = r * a;
        a = a * a;
        b >>= 1;
    }
    return r;
}
