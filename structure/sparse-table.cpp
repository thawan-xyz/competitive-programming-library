struct table {
    int n;
    matrix<int> table;
    array<int> pow2, log2;
    
    table(array<int> &a): n(a.size()), pow2(n + 1), log2(n + 1) {
        pow2[0] = 1;
        pow2[1] = 2;
        for (int i = 2; i <= n; ++i) {
            pow2[i] = pow2[i - 1] << 1;
            log2[i] = log2[i >> 1] + 1;
        }
        table.assign(n, array<int>(log2[n] + 1));
        for (int i = 0; i < n; ++i) {
            table[i][0] = a[i];
        }
        for (int k = 1; k <= log2[n]; ++k) {
            for (int i = 0; (i + pow2[k]) - 1 < n; ++i) {
                table[i][k] = min(table[i][k - 1], table[i + pow2[k - 1]][k - 1]);
            }
        }
    }
    
    int query(int l, int r) {
        int k = log2[(r - l) + 1];
        return min(table[l][k], table[(r - pow2[k]) + 1][k]);
    }
};
