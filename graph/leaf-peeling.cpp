// Leaf Peeling: finds the center(s) and diameter of an undirected tree
// Time: O(N) | Space: O(N)
// Note: returns {diameter, centers} | root is the first vertex, 0 or 1
pair<int, vector<int>> leaf_peeling(int root, vector<vector<int>> &g) {
    int n = g.size() - root, layers = 0;
    if (n == 1) return {0, {root}};
    vector<int> d(g.size()), leaves, next;
    for (int a = root; a < g.size(); ++a) {
        d[a] = g[a].size();
        if (d[a] == 1) leaves.push_back(a);
    }
    while (n > 2) {
        n -= leaves.size(), layers++;
        next.clear();
        for (int a : leaves) for (int b : g[a]) if (--d[b] == 1) next.push_back(b);
        swap(leaves, next);
    }
    return {2 * layers + (leaves.size() == 2), leaves};
}
