// Max Clique: Bron-Kerbosch with the pivot of most neighbors and pruning by the best size
// Time: O(3^(n / 3)) | Space: O(n)
// Note: for a maximum independent set, run it on the complement graph
vector<int> max_clique(vector<vector<int>> &g) {
    auto size = [](int x) -> int { return __builtin_popcountll(x); };
    auto first = [](int x) -> int { return __builtin_ctzll(x); };

    int n = g.size(), all = 0, best = 0;
    vector<int> adj(n);
    for (int a = 0; a < n; ++a) {
        all |= 1LL << a;
        for (int b : g[a]) if (b != a) {
            adj[a] |= 1LL << b;
        }
    }

    auto rec = [&](auto &self, int clique, int cand) -> void {
        if (size(clique) + size(cand) <= size(best)) return;
        if (cand == 0) return void(best = clique);
        int pivot = first(cand);
        for (int rest = cand; rest; rest &= rest - 1) {
            int v = first(rest);
            if (size(cand & adj[v]) > size(cand & adj[pivot])) pivot = v;
        }
        for (int rest = cand & ~adj[pivot]; rest; rest &= rest - 1) {
            int v = first(rest);
            self(self, clique | (1LL << v), cand & adj[v]);
            cand &= ~(1LL << v);
        }
    };
    rec(rec, 0, all);

    vector<int> res;
    for (int v = 0; v < n; ++v) if ((best >> v) & 1) res.push_back(v);
    return res;
}
