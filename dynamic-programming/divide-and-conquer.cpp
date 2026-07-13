int divide_and_conquer() {
    vector<int> prev(n + 1, inf);
    vector<int> curr(n + 1, inf);
    auto compute = [&](auto &self, int l, int r, int opt_l, int opt_r) -> void {
        if (l > r) return;
        int m = (l + r) / 2;
        curr[m] = inf;
        int opt = opt_l;
        for (int k = opt_l; k <= min(m - 1, opt_r); ++k) {
            int val = prev[k] + cost(k + 1, m);
            if (val < curr[m]) {
                curr[m] = val;
                opt = k;
            }
        }
        self(self, l, m - 1, opt_l, opt);
        self(self, m + 1, r, opt, opt_r);
    };
    prev[0] = 0;
    for (int i = 1; i <= k; ++i) {
        compute(compute, 1, n, 0, n - 1);
        prev = curr;
    }
    return curr[n];
}
