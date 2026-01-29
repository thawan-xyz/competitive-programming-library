int divide_and_conquer() {
    list<int> prev(n + 1, inf);
    list<int> curr(n + 1, inf);
    function<void(int, int, int, int)> compute = [&](int l, int r, int opt_l, int opt_r) -> void {
        if (l <= r) {
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
            compute(l, m - 1, opt_l, opt);
            compute(m + 1, r, opt, opt_r);
        }
    };
    prev[0] = 0;
    for (int i = 1; i <= k; ++i) {
        compute(1, n, 0, n - 1);
        prev = curr;
    }
    return curr[n];
}
