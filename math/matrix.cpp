// Matrix: product and fast power mod | counts walks of length k and linear recurrences
// Time: product O(N^3), power O(N^3 log K) | Space: O(N^2)
// Min-Plus: shortest walk with k edges | fill with inf and identity diagonal 0, r[i][j] = min(r[i][j], a[i][k] + b[k][j])
// Max-Plus: longest walk with k edges | fill with -inf and identity diagonal 0, r[i][j] = max(r[i][j], a[i][k] + b[k][j])
using matrix = vector<vector<int>>;

matrix operator*(const matrix &a, const matrix &b) {
    int n = a.size();
    int m = b[0].size();
    int h = b.size();
    matrix r(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < h; ++k) {
            for (int j = 0; j < m; ++j) {
                r[i][j] = (r[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    return r;
}

matrix mod_pow(matrix a, int e) {
    int n = a.size();
    matrix r(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        r[i][i] = 1;
    }
    while (e != 0) {
        if (e & 1) r = r * a;
        a = a * a;
        e >>= 1;
    }
    return r;
}
