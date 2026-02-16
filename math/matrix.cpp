struct matrix : list<list<int>> {
    matrix(int n, int m, int x = 0): list<list<int>>(n, list<int>(m, x)) {}

    matrix operator*(const matrix &b) const {
        const matrix &a = *this;
        int n = a.size();
        int m = b[0].size();
        int h = b.size();
        matrix r(n, m);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < h; ++k) {
                for (int j = 0; j < m; ++j) {
                    r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % mod;
                }
            }
        }
        return r;
    }

    matrix operator^(int b) const {
        matrix a = *this;
        int n = a.size();
        matrix r(n, n);
        for (int i = 0; i < n; ++i) r[i][i] = 1;
        while (b != 0) {
            if (b & 1) r = r * a;
            a = a * a;
            b >>= 1;
        }
        return r;
    }
};
