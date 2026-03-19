// FWHT / Bitwise Convolution: C[k] = sum(A[i] * B[j]) for i (OPR) j = k
// Time: O(N log N) | Space: O(N)
// Operation: 'A' (AND), 'O' (OR), 'X' (XOR)
void fwht(vector<int> &p, int sign, char opr) {
    int n = p.size();

    for (int half = 1; half < n; half *= 2) {
        for (int i = 0; i < n; i += 2 * half) {
            for (int j = 0; j < half; ++j) {
                int x = p[i + j];
                int y = p[(i + j) + half];
                if (opr == 'A') {
                    p[i + j] = ((x + sign * y) + mod) % mod;
                } else if (opr == 'O') {
                    p[(i + j) + half] = ((sign * x + y) + mod) % mod;
                } else if (opr == 'X') {
                    p[i + j] = (x + y) % mod;
                    p[(i + j) + half] = ((x - y) + mod) % mod;
                }
            }
        }
    }

    if (opr == 'X' and sign == -1) {
        int inv_n = mod_pow(n, mod - 2);
        for (int &i : p) i = (i * inv_n) % mod;
    }
}

vector<int> convolution(vector<int> a, vector<int> b, char opr) {
    int n = 1, m = max(a.size(), b.size());
    while (n < m) n *= 2;

    a.resize(n), b.resize(n);
    fwht(a, 1, opr), fwht(b, 1, opr);

    for (int i = 0; i < n; ++i) a[i] = (a[i] * b[i]) % mod;
    fwht(a, -1, opr);

    return a;
}
