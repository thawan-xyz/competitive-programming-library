list<list<int>> floyd_warshall(int n, list<list<int>> &g) {
    list<list<int>> d = g;
    for (int i = 0; i < n; ++i) {
        d[i][i] = 0;
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) if (d[i][k] != inf) {
            for (int j = 0; j < n; ++j) if (d[k][j] != inf) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    return d;
}
