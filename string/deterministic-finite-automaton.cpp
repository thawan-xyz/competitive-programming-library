vector<array<int, 26>> deterministic_finite_automaton(const string &s) {
    int n = s.length();
    vector<array<int, 26>> dfa(n + 1);
    if (n == 0) return dfa;
    dfa[0][s[0] - 'a'] = 1;
    for (int i = 1, j = 0; i <= n; ++i) {
        for (int c = 0; c < 26; ++c) {
            dfa[i][c] = dfa[j][c];
        }
        if (i < n) {
            dfa[i][s[i] - 'a'] = i + 1;
            j = dfa[j][s[i] - 'a'];
        }
    }
    return dfa;
}
