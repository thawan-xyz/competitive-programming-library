// Gaussian Elimination: solves A x = b from the augmented matrix a = [A | b], with n equations and m variables
// Time: O(n m min(n, m)) | Space: O(m) auxiliary
// Note: uses mod and mod_pow | a is int (values in [0, mod)) or float | returns {0: none, 1: unique, 2: infinite, x}, free variables are 0
template<class T> pair<int, vector<T>> gaussian_elimination(vector<vector<T>> &a) {
    constexpr bool real = is_floating_point_v<T>;
    auto fix = [](T x) -> T { if constexpr (real) return x; else return (x % mod + mod) % mod; };
    auto inv = [](T x) -> T { if constexpr (real) return 1 / x; else return mod_pow(x, mod - 2, mod); };
    auto zero = [](T x) -> bool { if constexpr (real) return abs(x) < 1e-9; else return x == 0; };

    int n = a.size(), m = a[0].size() - 1, r = 0;
    vector<int> col(n);
    for (int c = 0; c < m and r < n; ++c) {
        int k = r;
        for (int i = r; i < n; ++i) if (abs(a[i][c]) > abs(a[k][c])) k = i;
        if (zero(a[k][c])) continue;
        swap(a[r], a[k]);
        T d = inv(a[r][c]);
        for (int j = c; j <= m; ++j) a[r][j] = fix(a[r][j] * d);
        for (int i = 0; i < n; ++i) {
            if (i == r or zero(a[i][c])) continue;
            T f = a[i][c];
            for (int j = c; j <= m; ++j) a[i][j] = fix(a[i][j] - f * a[r][j]);
        }
        col[r++] = c;
    }
    for (int i = r; i < n; ++i) if (not zero(a[i][m])) return {0, {}};
    vector<T> x(m);
    for (int i = 0; i < r; ++i) x[col[i]] = a[i][m];
    return {r == m ? 1 : 2, x};
}
