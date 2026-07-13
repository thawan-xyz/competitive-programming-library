int divide_and_conquer() {
    vector<int> prev(n + 1, inf);
    vector<int> curr(n + 1, inf);
    auto compute = [&](auto &self, int l, int r, int opt_l, int opt_r) -> void {
        if (l > r) return;
        int m = (l + r) / 2;
        curr[m] = inf;
        int opt = opt_r;
        for (int i = max(opt_l, m); i <= min(opt_r, n - 1); ++i) if (prev[i + 1] != inf) {
            int val = cost(m, i) + prev[i + 1];
            if (val < curr[m]) {
                curr[m] = val;
                opt = i;
            }
        }
        self(self, l, m - 1, opt_l, opt);
        self(self, m + 1, r, opt, opt_r);
    };
    for (int i = 1; i <= n; ++i) {
        curr[i] = cost(i, n);
    }
    for (int i = 2; i <= k; ++i) {
        swap(prev, curr);
        compute(compute, 1, n, 1, n);
    }
    return curr[1];
}
