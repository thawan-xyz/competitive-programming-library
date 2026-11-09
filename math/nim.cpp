vector<int> grundy(int n, vector<int> &moves) {
    vector<int> g(n + 1), seen(moves.size() + 1, -1);
    for (int i = 1; i <= n; ++i) {
        for (int m : moves) if (m <= i) seen[g[i - m]] = i;
        while (seen[g[i]] == i) g[i]++;
    }
    return g;
}

bool nim(vector<int> &piles, vector<int> &moves) {
    vector<int> g = grundy(*max_element(piles.begin(), piles.end()), moves);
    int x = 0;
    for (int p : piles) x ^= g[p];
    return x != 0;
}

bool misere(vector<int> &piles) {
    int x = 0;
    for (int p : piles) x ^= p;
    if (*max_element(piles.begin(), piles.end()) > 1) return x != 0;
    return x == 0;
}
