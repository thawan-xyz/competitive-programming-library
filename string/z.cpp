array<int> z(str s) {
    int n = s.length();
    array<int> z(n);
    int low = 0, high = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= high) {
            z[i] = min(high - (i - 1), z[i - low]);
        }
        while (z[i] + i < n and s[z[i]] == s[z[i] + i]) {
            z[i]++;
        }
        if (z[i] + (i - 1) > high) {
            low = i, high = z[i] + (i - 1);
        }
    }
    return z;
}
