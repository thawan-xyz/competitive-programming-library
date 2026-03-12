/*
 * Algoritmo para encontrar Pontos de Articulação (Cut Vertices) em um Grafo Não-Direcionado
 * Retorna uma lista de vértices que, se removidos, aumentam o número de componentes conexos (desconectam o grafo).
 * Complexidade de Tempo: O(V + E)
 * Complexidade de Espaço: O(V)
 */
vector<int> articulations(int o, vector<vector<int>> &g) {
    int n = g.size(), timer = 1;
    vector<int> in(n), low(n);
    vector<bool> art(n);

    auto dfs = [&](auto &self, int a, int p) -> void {
        in[a] = low[a] = timer++;
        int c = 0;
        for (int b : g[a]) if (b != p) {
            if (in[b] != 0) {
                low[a] = min(low[a], in[b]);
            } else {
                c++;
                self(self, b, a);
                low[a] = min(low[a], low[b]);
                if (a != p and low[b] >= in[a]) art[a] = true;
            }
        }
        if (a == p and c > 1) art[a] = true;
    };

    vector<int> points;
    for (int i = o; i < n; ++i) {
        if (in[i] == 0) dfs(dfs, i, i);
        if (art[i]) points.push_back(i);
    }
    return points;
}
