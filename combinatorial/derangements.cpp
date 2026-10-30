// Derangements: number of permutations of N elements where no element stays in its place
// Time: O(N) | Space: O(N)
vector<int> derangements(int n) {
    vector<int> d(n + 1);
    d[0] = 1;
    for (int i = 2; i <= n; ++i) d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % mod;
    return d;
}
