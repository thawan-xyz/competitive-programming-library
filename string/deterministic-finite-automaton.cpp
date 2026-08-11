vector<vector<int>> deterministic_finite_automaton(string &s) {
    int n = s.length();
    vector<int> lps = longest_prefix_suffix(s);
    vector<vector<int>> dfa(n + 1, vector<int>(26));
    for (int i = 0; i <= n; ++i) {
        for (int c = 0; c < 26; ++c) {
            if (i < n and (s[i] - 'a') == c) {
                dfa[i][c] = i + 1;
            } else if (i > 0) {
                dfa[i][c] = dfa[lps[i - 1]][c];
            } else {
                dfa[i][c] = 0;
            }
        }
    }
    return dfa;
}
