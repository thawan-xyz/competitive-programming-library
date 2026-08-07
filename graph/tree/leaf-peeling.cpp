// Leaf Peeling: finds the center(s) and diameter of an undirected tree
// Time: O(N) | Space: O(N)
// Note: returns {centers, diameter} | 'i' sets 0-based or 1-based indexing
pair<int, vector<int>> leaf_peeling(int i, vector<vector<int>> &g) {
    int n = g.size() - i;
    if (n == 1) return {0, {i}};
    vector<int> d(g.size());
    queue<int> q;
    for (int a = i; a < g.size(); ++a) {
        d[a] = g[a].size();
        if (d[a] == 1) q.push(a);
    }
    int r = n, l = 0;
    while (r > 2) {
        int s = q.size();
        r -= s;
        l++;
        while (s--) {
            int a = q.front(); q.pop();
            for (int b : g[a]) {
                if (--d[b] == 1) q.push(b);
            }
        }
    }
    vector<int> c;
    while (q.size()) c.push_back(q.front()), q.pop();
    return {c, 2 * l + (c.size() == 2)};
}
