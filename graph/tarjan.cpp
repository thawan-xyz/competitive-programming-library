void tarjan() {
    int timer = 0;
    array<array<int>> graph;
    array<int> tin, low;
    array<bool> visited, articulation;
    array<pair<int, int>> bridges;
    
    function<void(int, int)> dfs = [&](int a, int p) -> void {
        visited[a] = true;
        tin[a] = low[a] = timer++;
        
        for (int b : graph[a]) {
            if (b == p) continue;
            
            if (visited[b]) {
                low[a] = min(low[a], tin[b]);
            } else {
                dfs(b, a);
                low[a] = min(low[a], low[b]);
                
                if (tin[a] < low[b]) bridges.emplace_back(a, b);
                if (p != -1 and tin[a] <= low[b]) articulation[a] = true;
            }
        }
        if (p == -1 and graph[a].size() > 1) articulation[a] = true;
    };
}
