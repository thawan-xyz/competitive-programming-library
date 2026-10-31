// Fast Walsh-Hadamard Transform: bitwise convolution, c[k] = sum of a[i] * b[j] over i opr j = k, with opr = '&', '|' or '^'
// Time: O(N log N) | Space: O(N)
void fwht(vector<int> &f, char opr, bool inv) {
    int n = f.size();
    for (int k = 1; k < n; k *= 2) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = i; j < i + k; ++j) {
                int x = f[j], y = f[j + k];
                if (opr == '&') x += (inv) ? mod - y : y;
                if (opr == '|') y += (inv) ? mod - x : x;
                if (opr == '^') tie(x, y) = pair(x + y, x - y + mod);
                f[j] = x - (x >= mod) * mod, f[j + k] = y - (y >= mod) * mod;
            }
        }
    }
    if (opr == '^' and inv) {
        int inv_n = mod_pow(n, mod - 2, mod);
        for (int &x : f) x = x * inv_n % mod;
    }
}

vector<int> convolution(vector<int> a, vector<int> b, char opr) {
    int n = 1;
    while (n < max(a.size(), b.size())) n *= 2;
    a.resize(n), b.resize(n);
    fwht(a, opr, false), fwht(b, opr, false);
    for (int i = 0; i < n; ++i) a[i] = a[i] * b[i] % mod;
    fwht(a, opr, true);
    return a;
}
