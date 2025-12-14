int linear_recurrence(int n, int k, list<int> &c, list<int> &f) {
    if (n < k) return f[n];

    matrix m(k, list<int>(k));
    for (int i = 0; i < k; ++i) m[0][i] = c[i];
    for (int i = 1; i < k; ++i) m[i][i - 1] = 1;

    matrix p = pow(m, n - k + 1);

    int answer = 0;
    for (int i = 0; i < k; ++i) {
        answer += (p[0][i] * f[i]) % mod;
        answer %= mod;
    }
    return answer;
}

int linear_recurrence_constant(int n, int k, list<int> &c, int constant, list<int> &f) {
    if (n < k) return f[n];

    matrix m(k + 1, list<int>(k + 1));
    for (int i = 0; i < k; ++i) m[0][i] = c[i];
    m[0][k] = 1;
    for (int i = 1; i < k; ++i) m[i][i - 1] = 1;
    m[k][k] = 1;

    matrix p = pow(m, n - k + 1);

    int answer = 0;
    for (int i = 0; i < k; ++i) {
        answer += (p[0][i] * f[i]) % mod;
        answer %= mod;
    }
    answer += (p[0][k] * constant) % mod;
    return answer % mod;
}
