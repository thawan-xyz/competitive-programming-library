vector<int> maximum_clique(vector<vector<int>> &g) {
    int n = g.size();
    vector<int> h(n);
    for (int a = 0; a < n; ++a) {
        for (int b : g[a]) {
            h[a] |= 1LL << b;
        }
    }
    int size = 0, mask = 0;
    auto bron_kerbosch = [&](auto &self, int r, int p, int x) -> void {
        if (p == 0 and x == 0) {
            int s = __builtin_popcountll(r);
            if (s > size) {
                size = s;
                mask = r;
            }
            return;
        }
        int i = __builtin_ctzll(p | x);
        int c = p & ~h[i];
        while (c) {
            int k = __builtin_ctzll(c);
            int k_mask = 1LL << k;
            self(self, r | k_mask, p & h[k], x & h[k]);
            p ^= k_mask;
            x |= k_mask;
            c ^= k_mask;
        }
    };
    int initial = (1LL << n) - 1;
    bron_kerbosch(bron_kerbosch, 0, initial, 0);
    vector<int> clique;
    for (int i = 0; i < n; ++i) {
        if ((mask >> i) & 1) {
            clique.push_back(i);
        }
    }
    return clique;
}
