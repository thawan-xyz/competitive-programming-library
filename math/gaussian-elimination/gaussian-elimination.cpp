// Gaussian Elimination: solves systems of linear equations (modulo arithmetic)
// Time: O(N * M^2) | Space: O(M) auxiliary
// Note: returns {(0: none, 1: unique, 2: infinite), solution}
pair<int, vector<int>> gaussian_elimination(matrix &a, const int mod) {
    int n = a.size(), m = a[0].size() - 1;
    vector<int> p(m, -1);
    int r, c;
    for (r = 0, c = 0; r < n and c < m; ++c) {
        int k = r;
        for (int i = r + 1; i < n and a[k][c] == 0; ++i) k = i;
        if (a[k][c] == 0) continue;

        swap(a[r], a[k]);
        p[r] = c;

        int inv = mod_pow(a[r][c], mod - 2, mod);
        for (int j = c; j <= m; ++j) {
            a[r][j] = (a[r][j] * inv) % mod;
        }

        for (int i = 0; i < n; ++i) if (i != r and a[i][c] != 0) {
            int f = mod - a[i][c];
            for (int j = c; j <= m; ++j) {
                a[i][j] = (a[i][j] + f * a[r][j]) % mod;
            }
        }
        ++r;
    }
    for (int i = r; i < n; ++i) if (a[i][m] != 0) {
        return {0, {}};
    }
    vector<int> x(m);
    for (int i = 0; i < r; ++i) {
        x[p[i]] = a[i][m];
    }
    return {(r == m) ? 1 : 2, x};
}

// Gaussian Elimination: solves systems of linear equations (floating-point with partial pivoting)
// Time: O(N * M^2) | Space: O(M) auxiliary
// Note: returns {(0: none, 1: unique, 2: infinite), solution}. Uses 'eps' for numerical stability.
pair<int, vector<float>> gaussian_elimination(matrix &a, const float eps) {
    int n = a.size(), m = a[0].size() - 1;
    vector<int> p(m, -1);
    int r, c;
    for (r = 0, c = 0; r < n and c < m; ++c) {
        int k = r;
        for (int i = r + 1; i < n; ++i) if (abs(a[i][c]) > abs(a[k][c])) k = i;
        if (abs(a[k][c]) < eps) continue;

        swap(a[r], a[k]);
        p[r] = c;

        float d = a[r][c];
        for (int j = c; j <= m; ++j) {
            a[r][j] /= d;
        }

        for (int i = 0; i < n; ++i) if (i != r and abs(a[i][c]) > eps) {
            float f = a[i][c];
            for (int j = c; j <= m; ++j) {
                a[i][j] -= f * a[r][j];
            }
        }
        ++r;
    }
    for (int i = r; i < n; ++i) if (abs(a[i][m]) > eps) {
        return {0, {}};
    }
    vector<float> x(m);
    for (int i = 0; i < r; ++i) {
        x[p[i]] = a[i][m];
    }
    return {(r == m) ? 1 : 2, x};
}
