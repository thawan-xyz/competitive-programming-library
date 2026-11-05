int knuth(int n) {
    vector<vector<int>> ans(n + 2, vector<int>(n + 2));
    vector<vector<int>> opt(n + 2, vector<int>(n + 2));
    for (int l = n; l >= 1; --l) {
        ans[l][l] = cost(l, l);
        opt[l][l] = l;
        for (int r = l + 1; r <= n; ++r) {
            int c = cost(l, r);
            ans[l][r] = inf;
            for (int k = opt[l][r - 1]; k <= min(r - 1, opt[l + 1][r]); ++k) {
                int val = ans[l][k] + ans[k + 1][r] + c;
                if (val < ans[l][r]) ans[l][r] = val, opt[l][r] = k;
            }
        }
    }
    return ans[1][n];
}
