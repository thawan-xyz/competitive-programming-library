// Parallel Binary Search: for each query, the first update after which it is true, with all binary searches together
// Time: O((N + Q) log N) calls of insert and check | Space: O(N + Q)
// Note: check(k) must stay true after it becomes true, returns -1 if it never does, reset clears and insert(i) adds update i
vector<int> parallel_binary_search(int n, int q, auto reset, auto insert, auto check) {
    vector<int> low(q, 0), high(q, n - 1), ans(q, -1);
    while (true) {
        vector<vector<int>> at(n);
        bool done = true;
        for (int k = 0; k < q; ++k) {
            if (low[k] <= high[k]) {
                int i = (low[k] + high[k]) / 2;
                at[i].push_back(k);
                done = false;
            }
        }
        if (done) break;
        reset();
        for (int i = 0; i < n; ++i) {
            insert(i);
            for (int k : at[i]) {
                if (check(k)) {
                    ans[k] = i;
                    high[k] = i - 1;
                } else {
                    low[k] = i + 1;
                }
            }
        }
    }
    return ans;
}
