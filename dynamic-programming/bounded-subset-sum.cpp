// Bounded Subset Sum: maximizes subset sum without exceeding the target
// Time: O(N * max(W)) | Space: O(max(W))
// Note: efficient for huge targets with small weights
int bounded_subset_sum(const vector<int> &w, int target) {
    int n = w.size(), k = 0, s = 0;
    while (k < n and s + w[k] <= target) s += w[k++];
    if (k == n) return s;
    int m = *max_element(w.begin(), w.end());
    vector<int> pre;
    vector<int> cur(2 * m, -1);
    cur[s - target + m] = k;
    for (int i = k; i < n; ++i) {
        pre = cur;
        for (int x = 0; x < m; ++x) {
            cur[x + w[i]] = max(cur[x + w[i]], pre[x]);
        }
        for (int x = 2 * m - 1; x > m; --x) {
            for (int j = max<int>(0, pre[x]); j < cur[x]; ++j) {
                cur[x - w[j]] = max(cur[x - w[j]], j);
            }
        }
    }
    int x = m;
    while (cur[x] == -1) x--;
    return x + target - m;
}
