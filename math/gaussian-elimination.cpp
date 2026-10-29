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

// XOR Gaussian Elimination: solves XOR systems (mod 2)
// Time: O(N * n * m / 64) | Space: O(N * m / 64) auxiliary
// Note: returns {(-1: none, r: rank), solution} | 2^(n - r) solutions and undetermined vars = d
template<int N> pair<int, vector<int>> xor_gaussian_elimination(int n, vector<bitset<N + 1>> a, int d) {
    int m = a.size(), r = 0;
    vector<int> where(n, -1);
    for (int c = 0; c < n and r < m; ++c) {
        int p = r;
        while (p < m and not a[p][c]) {
            p++;
        }
        if (p == m) continue;
        swap(a[r], a[p]);
        for (int i = 0; i < m; ++i) {
            if (i != r and a[i][c]) a[i] ^= a[r];
        }
        where[c] = r++;
    }
    for (int i = r; i < m; ++i) {
        if (a[i][n]) return {-1, {}};
    }
    vector<int> x(n, d);
    bitset<N + 1> ones;
    for (int j = 0; j < n; ++j) {
        if (where[j] == -1) ones[j] = d;
    }
    for (int j = 0; j < n; ++j) {
        if (where[j] != -1) x[j] = a[where[j]][n] ^ ((a[where[j]] & ones).count() & 1);
    }
    return {r, x};
}
