list<int> z_array(str &s) {
    int n = s.length();
    list<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        z[i] = max(0, min(z[i - l], r - (i + 1)));
        while (i + z[i] < n and s[i + z[i]] == s[z[i]]) {
            l = i;
            r = i + z[i];
            z[i] += 1;
        }
    }
    return z;
}
