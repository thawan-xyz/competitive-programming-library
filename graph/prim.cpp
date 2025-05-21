const long inf = 1e18;
using graph = array<array<pair<int, long>>>;

graph prim(int n, graph &g) {
    graph mst(n);
    long cost = 0;
    array<int> parent(n, -1);
    array<bool> visited(n);
    array<long> distance(n, inf);
    priority_queue<pair<long, int>> p;
    
    distance[0] = 0;
    p.emplace(0, 0);
    while (p.size() > 0) {
        auto [d, a] = p.top(); p.pop();
        if (visited[a]) continue;
        
        visited[a] = true; d *= -1;
        cost += d;
        if (parent[a] != -1) {
            mst[parent[a]].emplace_back(a, d);
            mst[a].emplace_back(parent[a], d);
        }
        
        for (auto &[b, w] : g[a]) {
            if (not visited[b] and w < distance[b]) {
                distance[b] = w;
                parent[b] = a;
                p.emplace(-w, b);
            }
        }
    }
    return mst;
}
