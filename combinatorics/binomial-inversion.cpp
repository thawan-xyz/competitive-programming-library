// Binomial Inversion: transforms subset group counts into exact frequency counts
// Time: O(n^2) | Space: O(n)
// Formula: exact[i] = sum_{j=i}^{n} (-1)^(j-i) * C(j, i) * subsets[j]
vector<int> binomial_inversion(const vector<int> &subsets) {
    int n = subsets.size() - 1;
    vector<int> exact(n + 1);
    for (int i = 0; i <= n; ++i) {
        int count = 0;
        for (int j = i; j <= n; ++j) {
            int term = (C(j, i) * subsets[j]) % mod;
            if ((j - i) & 1) {
                count = (count - term + mod) % mod;
            } else {
                count = (count + term) % mod;
            }
        }
        exact[i] = count;
    }
    return exact;
}
