// Divide and Conquer on Queries: answers offline range queries [i, j] at the middle m of the first range that splits them
// Time: O((N + Q) log N) | Space: O(N + Q)
// Note: suf[i] = answer of arr[i..m] and pre[j] = answer of arr[m+1..j] | edit both sweeps and suf[i] + pre[j]
vector<int> dnc_queries(vector<int> &arr, vector<array<int, 2>> &que) {
    int n = arr.size();
    vector<int> suf(n + 1), pre(n + 1), ans(que.size());
    vector<array<int, 3>> h;
    for (int k = 0; k < que.size(); ++k) h.push_back({que[k][0], que[k][1], k});
    auto rec = [&](auto &self, int l, int r, span<array<int, 3>> q) -> void {
        if (l > r or q.empty()) return;
        int m = (l + r) / 2;
        suf[m + 1] = 0;
        for (int i = m; i >= l; --i) suf[i] = arr[i] + suf[i + 1];
        pre[m] = 0;
        for (int j = m + 1; j <= r; ++j) pre[j] = pre[j - 1] + arr[j];
        auto cross = partition(q.begin(), q.end(), [&](auto &x) { return x[1] < m; });
        auto right = partition(cross, q.end(), [&](auto &x) { return x[0] <= m; });
        for (auto [i, j, k] : span(cross, right)) ans[k] = suf[i] + pre[j];
        self(self, l, m - 1, span(q.begin(), cross));
        self(self, m + 1, r, span(right, q.end()));
    };
    rec(rec, 0, n - 1, h);
    return ans;
}
