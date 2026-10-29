// Berlekamp-Massey: finds the shortest linear recurrence of a sequence
// Time: O(N^2) where N is sequence size | Space: O(N)
// Note: requires at least 2L terms to correctly find a recurrence of length L
vector<int> berlekamp_massey(const vector<int> &seq) {
    vector<int> old = {1}, curr = {1};
    int prev = 1, len = 0, shift = 1;
    for (int i = 0; i < seq.size(); ++i) {
        int delta = 0;
        for (int j = 0; j <= len; ++j) {
            delta = (delta + curr[j] * seq[i - j]) % mod;
        }
        if (delta == 0) {
            shift++;
            continue;
        } 
        vector<int> temp = curr;
        int mult = (mod - (delta * mod_pow(prev, mod - 2)) % mod) % mod;
        if (curr.size() <= old.size() + shift) {
            curr.resize(old.size() + shift + 1, 0);
        }
        for (int j = 0; j < old.size(); ++j) {
            curr[j + shift] = (curr[j + shift] + mult * old[j]) % mod;
        }
        if (2 * len <= i) {
            len = i + 1 - len;
            old = temp;
            prev = delta;
            shift = 1;
        } else {
            shift++;
        }
    }
    vector<int> coef(len);
    for (int i = 1; i <= len; ++i) {
        coef[i - 1] = (mod - curr[i]) % mod;
    }
    return coef;
}

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
