vector<array<int, 26>> prefix_automaton(const string &s) {
    int n = s.size();
    vector<array<int, 26>> aut(n + 1);
    if (n > 0) aut[0][s[0] - 'a'] = 1;
    for (int i = 1, j = 0; i <= n; ++i) {
        aut[i] = aut[j];
        if (i < n) {
            aut[i][s[i] - 'a'] = i + 1;
            j = aut[j][s[i] - 'a'];
        }
    }
    return aut;
}
