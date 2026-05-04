// Gaussian Elimination: solves systems of linear equations (modulo arithmetic)
// Time: O(N * M^2) | Space: O(M) auxiliary
// Note: returns {(0: none, 1: unique, 2: infinite), solution}
pair<int, vector<int>> gaussian_elimination(matrix &a, const int mod) {
    int n = a.size(), m = a[0].size() - 1;
    vector<int> p(m, -1);
    int r, c;
    for (r = 0, c = 0; r < n and c < m; ++c) {
        int k = -1;
        for (int i = r; k < 0 and i < n; ++i) if (a[i][c] != 0) {
            k = i;
        }
        if (k < 0) continue;

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
