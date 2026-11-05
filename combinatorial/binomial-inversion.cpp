// Binomial Inversion: transforms subset group counts into exact frequency counts
// Time: O(n^2) | Space: O(n)
// Formula: exact[i] = sum_{j=i}^{n} (-1)^(j-i) * comb(j, i) * subsets[j]
vector<int> binomial_inversion(const vector<int> &subsets) {
    int n = subsets.size() - 1;
    vector<int> exact(n + 1);
    for (int i = 0; i <= n; ++i) {
        int cnt = 0;
        for (int j = i; j <= n; ++j) {
            int term = (comb(j, i) * subsets[j]) % mod;
            if ((j - i) & 1) {
                cnt = (cnt - term + mod) % mod;
            } else {
                cnt = (cnt + term) % mod;
            }
        }
        exact[i] = cnt;
    }
    return exact;
}
