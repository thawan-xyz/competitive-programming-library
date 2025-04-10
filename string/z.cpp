array<int> z(str &s) {
    int n = s.length();
    array<int> a(n);

    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            a[i] = min(r - (i - 1), a[i - l]);
        }

        while (a[i] + i < n and s[a[i]] == s[a[i] + i]) {
            a[i]++;
        }
        if (a[i] + (i - 1) > r) {
            l = i, r = a[i] + (i - 1);
        }
    }
    return a;
}
