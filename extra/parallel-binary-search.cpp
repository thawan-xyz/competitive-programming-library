// Parallel Binary Search: for each query, the first update after which it is true, with all binary searches together
// Time: O((N + Q) log N) calls of insert and check | Space: O(N + Q)
// Note: check(i) must stay true after it becomes true, returns -1 if it never does, reset clears and insert(i) adds update i
vector<int> parallel_binary_search(int n, int q, auto reset, auto insert, auto check) {
    vector<int> low(q, 0), high(q, n - 1), ans(q, -1);
    while (true) {
        vector<vector<int>> at(n);
        bool done = true;
        for (int i = 0; i < q; ++i) {
            if (low[i] <= high[i]) {
                int mid = (low[i] + high[i]) / 2;
                at[mid].push_back(i);
                done = false;
            }
        }
        if (done) break;
        reset();
        for (int mid = 0; mid < n; ++mid) {
            insert(mid);
            for (int i : at[mid]) {
                if (check(i)) {
                    ans[i] = mid;
                    high[i] = mid - 1;
                } else {
                    low[i] = mid + 1;
                }
            }
        }
    }
    return ans;
}
