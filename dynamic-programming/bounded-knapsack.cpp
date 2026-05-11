bool bounded_knapsack(vector<int> &w, int target) {
    int n = w.size();
    int k = 0, s = 0;
    while (k < n and s + w[k] <= target) s += w[k++];

    if (s == target) return true;
    if (k == n) return false;

    int bound = *max_element(w.begin(), w.end());
    int offset = target - bound;
    
    vector<int> prev(2 * bound + 1, -1);
    prev[s - offset] = k;

    for (int i = k; i < n; ++i) {
        vector<int> curr = prev;

        // insert
        for (int x = 0; x <= 2 * bound - w[i]; ++x) if (prev[x] != -1) {
            curr[x + w[i]] = max(curr[x + w[i]], prev[x]);
        }

        // remove
        for (int x = 2 * bound; x >= 0; --x) if (curr[x] > prev[x]) {
            for (int j = curr[x] - 1; j >= max<int>(0, prev[x]); --j) {
                int y = x - w[j];
                if (y >= 0) curr[y] = max(curr[y], j);
            }
        }

        if (curr[target - offset] != -1) return true;
        swap(prev, curr);
    }
    return false;
}
