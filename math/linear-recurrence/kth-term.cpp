// Linear Recurrence K-th Term: computes the K-th term of a sequence
// Time: O(L^2 log K) where L is recurrence length | Space: O(L)
// Note: 0-indexed | the sequence must have at least L terms
int kth_term(int k, const vector<int> &seq, const vector<int> &coef) {
    if (k < seq.size()) return seq[k];
    if (coef.empty()) return 0;

    int n = coef.size();

    auto combine = [&](const vector<int> &a, const vector<int> &b) -> vector<int> {
        vector<int> r(2 * n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                r[i + j] = (r[i + j] + a[i] * b[j]) % mod;
            }
        }
        for (int i = 2 * n - 2; i >= n; --i) {
            for (int j = 0; j < n; ++j) {
                r[i - j - 1] = (r[i - j - 1] + r[i] * coef[j]) % mod;
            }
        }
        r.resize(n);
        return r;
    };

    vector<int> pol(n), exp(n);
    pol[0] = 1;
    if (n > 1) exp[1] = 1;
    else exp[0] = coef[0];

    while (k != 0) {
        if (k & 1) pol = combine(pol, exp);
        exp = combine(exp, exp);
        k >>= 1;
    }

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = (ans + pol[i] * seq[i]) % mod;
    }
    return ans;
}
