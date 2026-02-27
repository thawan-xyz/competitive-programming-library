int knuth() {
    vector<vector<int>> val(n + 5, vector<int>(n + 5));
    vector<vector<int>> opt(n + 5, vector<int>(n + 5));
    for (int i = 1; i <= n; ++i) {
        val[i][i] = cost(i, i);
        opt[i][i] = i;
    }
    for (int len = 2; len <= n; ++len) {
        for (int l = 1, r = len; r <= n; ++l, ++r) {
            val[l][r] = inf;
            opt[l][r] = opt[l][r - 1];
            for (int k = opt[l][r - 1]; k <= opt[l + 1][r]; ++k) {
                int curr = val[l][k] + val[k + 1][r] + cost(l, r);
                if (curr < val[l][r]) {
                    val[l][r] = curr;
                    opt[l][r] = k;
                }
            }
        }
    }
    return val[1][n];
}
