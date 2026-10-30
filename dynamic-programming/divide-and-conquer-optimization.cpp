// Divide and Conquer Optimization: minimum cost to split 1..n into k contiguous groups, where group [l, r] costs cost(l, r)
// Time: O(K N log N) calls of cost | Space: O(N)
// Note: needs cost(l, r) and inf | works when the best end of the first group never moves left as its start grows (quadrangle inequality)
int divide_and_conquer_optimization(int n, int k) {
    vector<int> prev(n + 2, inf), curr(n + 2, inf);
    prev[n + 1] = 0;
    auto solve = [&](auto &self, int l, int r, int low, int high) -> void {
        if (l > r) return;
        int m = (l + r) / 2, opt = high;
        curr[m] = inf;
        for (int i = max(m, low); i <= high; ++i) if (prev[i + 1] < inf) {
            int val = cost(m, i) + prev[i + 1];
            if (val < curr[m]) curr[m] = val, opt = i;
        }
        self(self, l, m - 1, low, opt);
        self(self, m + 1, r, opt, high);
    };
    for (int i = 1; i <= k; ++i) {
        solve(solve, 1, n, 1, n);
        curr[n + 1] = inf;
        swap(prev, curr);
    }
    return prev[1];
}
