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
