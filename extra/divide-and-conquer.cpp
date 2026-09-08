vector<int> divide_and_conquer() {
    int n, k;
    vector<int> a(n + 1);
    vector<int> pref(n + 2), suf(n + 2);
    vector<int> ans(k + 1);
    auto rec = [&](auto &rec, int low, int high, vector<tuple<int, int, int>> &q) -> void {
        if (low > high or q.empty()) return;
        int mid = (low + high) / 2;
        pref[mid + 1] = 0;
        suf[mid] = 0;
        for (int i = mid; i >= low; --i) pref[i] = a[i] + pref[i + 1];
        for (int i = mid + 1; i <= high; ++i) suf[i] = a[i] + suf[i - 1];
        vector<tuple<int, int, int>> ql, qr;
        for (auto [l, r, i] : q) {
            if (r < mid) ql.push_back({l, r, i});
            else if (l > mid) qr.push_back({l, r, i});
            else ans[i] = pref[l] + suf[r];
        }
        rec(rec, low, mid - 1, ql);
        rec(rec, mid + 1, high, qr);
    };
    return ans;
}
