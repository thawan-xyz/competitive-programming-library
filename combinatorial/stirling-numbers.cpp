// Stirling Numbers of the First Kind: t[i][k] = permutations of i elements with exactly k cycles, for i, k <= n
// Time: O(N^2) | Space: O(N^2)
// Note: uses mod (any) | c(i, k) = (i - 1) c(i - 1, k) + c(i - 1, k - 1) | signed = (-1)^(i - k) t[i][k]
vector<vector<int>> stirling1_table(int n) {
    vector<vector<int>> t(n + 1, vector<int>(n + 1));
    t[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int k = 1; k <= i; ++k) t[i][k] = (t[i - 1][k - 1] + (i - 1) * t[i - 1][k]) % mod;
    }
    return t;
}

// Stirling Numbers of the Second Kind: t[i][k] = ways to split i elements into exactly k non-empty groups, for i, k <= n
// Time: O(N^2) | Space: O(N^2)
// Note: uses mod (any) | S(i, k) = k S(i - 1, k) + S(i - 1, k - 1)
vector<vector<int>> stirling2_table(int n) {
    vector<vector<int>> t(n + 1, vector<int>(n + 1));
    t[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int k = 1; k <= i; ++k) t[i][k] = (t[i - 1][k - 1] + k * t[i - 1][k]) % mod;
    }
    return t;
}

// Stirling Row of the First Kind: row[k] = c(n, k) for k <= n, the coefficients of x (x + 1) ... (x + n - 1)
// Time: O(N log^2 N) | Space: O(N)
// Note: uses mod and convolution (mod must work with the NTT) | multiplies the factors (x + i) for i in [l, r) by divide and conquer
vector<int> stirling1_row(int n, int l = 0, int r = -1) {
    if (r == -1) r = n;
    if (l == r) return {1};
    if (r - l == 1) return {l, 1};
    int m = (l + r) / 2;
    return convolution<mod>(stirling1_row(n, l, m), stirling1_row(n, m, r));
}

// Stirling Row of the Second Kind: row[k] = S(n, k) for k <= n, with one convolution
// Time: O(N log N) | Space: O(N)
// Note: uses mod, mod_pow, invf (inverse factorials up to n) and convolution (mod must work with the NTT) | convolves (-1)^i / i! with j^n / j!
vector<int> stirling2_row(int n) {
    vector<int> a(n + 1), b(n + 1);
    for (int i = 0; i <= n; ++i) {
        a[i] = i % 2 == 0 ? invf[i] : mod - invf[i];
        b[i] = mod_pow(i, n, mod) * invf[i] % mod;
    }
    vector<int> row = convolution<mod>(a, b);
    row.resize(n + 1);
    return row;
}

// Stirling Number of the Second Kind: S(n, k) for a single pair, by inclusion-exclusion on the empty groups
// Time: O(k log n) | Space: O(1)
// Note: uses mod (prime), mod_pow and invf (inverse factorials up to k) | S(n, k) = sum of (-1)^(k - j) j^n / (j! (k - j)!)
int stirling2(int n, int k) {
    int s = 0;
    for (int j = 0; j <= k; ++j) {
        int term = mod_pow(j, n, mod) * invf[j] % mod * invf[k - j] % mod;
        s = (k - j) % 2 == 0 ? (s + term) % mod : (s - term + mod) % mod;
    }
    return s;
}
