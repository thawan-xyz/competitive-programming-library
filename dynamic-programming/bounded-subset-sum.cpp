// Bounded Subset Sum: maximizes subset sum without exceeding the target
// Time: O(N * max(W)) | Space: O(max(W))
// Note: efficient for huge targets with small weights
int bounded_subset_sum(vector<int> &w, int target) {
    int k = 0, s = 0;
    while (k < w.size() and s + w[k] <= target) s += w[k++];

    if (k == w.size() or s == target) return s;

    int bound = *max_element(w.begin(), w.end());
    int offset = target - bound;
    
    vector<int> prev(2 * bound + 1, -1);
    prev[s - offset] = k;

    for (int i = k; i < w.size(); ++i) {
        vector<int> curr = prev;

        // insert
        for (int x = 0; x < bound; ++x) if (prev[x] != -1) {
            curr[x + w[i]] = max(curr[x + w[i]], prev[x]);
        }

        // remove
        for (int x = 2 * bound; x > bound; --x) if (curr[x] > prev[x]) {
            for (int j = max(0ll, prev[x]); j < curr[x]; ++j) {
                curr[x - w[j]] = max(curr[x - w[j]], j);
            }
        }

        swap(prev, curr);
    }

    for (int x = bound; x >= 0; --x) if (prev[x] != -1) {
        return x + offset;
    }
    return 0;
}
