int linear_recurrence(int n, int k, array<int> &c, array<int> &f) {
    if (n < k) return f[n];

    matrix m(k, array<int>(k));
    for (int i = 0; i < k; ++i) m[0][i] = c[i];
    for (int i = 1; i < k; ++i) m[i][i - 1] = 1;

    matrix p = pow(m, n - k + 1);

    int answer = 0;
    for (int i = 0; i < k; ++i) {
        answer += (p[0][i] * f[k - (i + 1)]) % mod;
        answer %= mod;
    }
    return answer;
}

int linear_recurrence_constant(int n, int k, array<int> &c, int constant, array<int> &f) {
    if (n < k) return f[n];

    matrix m(k + 1, array<int>(k + 1));
    for (int i = 0; i < k; ++i) m[0][i] = c[i];
    m[0][k] = 1;
    for (int i = 1; i < k; ++i) m[i][i - 1] = 1;
    m[k][k] = 1;

    matrix p = pow(m, n - k + 1);

    int answer = 0;
    for (int i = 0; i < k; ++i) {
        answer += (p[0][i] * f[k - (i + 1)]) % mod;
        answer %= mod;
    }
    answer += (p[0][k] * constant) % mod;
    return answer % mod;
}
