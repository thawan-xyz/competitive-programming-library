vector<int> longest_prefix_suffix(str &s) {
    int n = s.length();
    vector<int> lps(n);
    for (int i = 1; i < n; ++i) {
        int j = lps[i - 1];
        while (j != 0 and s[i] != s[j]) {
            j = lps[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        lps[i] = j;
    }
    return lps;
}
