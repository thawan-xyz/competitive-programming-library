// Divide and Conquer on Queries: answers offline range queries [i, j] at the middle m of the first range that splits them
// Time: O((N + Q) log N) | Space: O(N + Q)
// Note: suf[i] = answer of arr[i..m] and pre[j] = answer of arr[m+1..j] | edit both sweeps and suf[i] + pre[j]
vector<int> divide_and_conquer_queries(vector<int> &arr, vector<array<int, 2>> &queries) {
    int n = arr.size();
    vector<int> suf(n + 1), pre(n + 1), ans(queries.size());
    vector<array<int, 3>> q;
    for (int k = 0; k < queries.size(); ++k) q.push_back({queries[k][0], queries[k][1], k});

    auto rec = [&](auto &self, int l, int r, vector<array<int, 3>> &q) -> void {
        if (l > r or q.empty()) return;
        int m = (l + r) / 2;
        suf[m + 1] = 0;
        for (int i = m; i >= l; --i) suf[i] = arr[i] + suf[i + 1];
        pre[m] = 0;
        for (int j = m + 1; j <= r; ++j) pre[j] = pre[j - 1] + arr[j];
        vector<array<int, 3>> ql, qr;
        for (auto [i, j, k] : q) {
            if (j < m) ql.push_back({i, j, k});
            else if (i > m) qr.push_back({i, j, k});
            else ans[k] = suf[i] + pre[j];
        }
        q.clear(), q.shrink_to_fit();
        self(self, l, m - 1, ql);
        self(self, m + 1, r, qr);
    };

    rec(rec, 0, n - 1, q);
    return ans;
}
