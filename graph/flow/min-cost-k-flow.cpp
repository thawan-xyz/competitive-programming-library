// Min Cost K-Flow: sends up to k units from s to t with minimum total cost, by successive shortest paths
// Time: O(F E log V) | Space: O(V + E)
// Note: if all costs are non-negative, replace spfa with fill(h.begin(), h.end(), 0)
struct min_cost_k_flow {
    struct edge {
        int b, i, w, c;
        bool o;
    };

    int n;
    vector<vector<edge>> g;
    vector<int> d, h, p, e;

    min_cost_k_flow(int n): n(n), g(n), d(n), h(n), p(n), e(n) {}

    void insert_edge(int a, int b, int w, int c) {
        int i = g[b].size(), j = g[a].size();
        g[a].push_back({b, i, w, c, true});
        g[b].push_back({a, j, 0, -c, false});
    }

    bool dijkstra(int s, int t) {
        fill(d.begin(), d.end(), inf);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        d[s] = 0;
        pq.push({0, s});
        while (pq.size()) {
            auto [x, a] = pq.top(); pq.pop();
            if (d[a] < x) continue;
            for (int i = 0; i < g[a].size(); ++i) {
                auto [b, j, w, c, o] = g[a][i];
                int v = d[a] + c + h[a] - h[b];
                if (w == 0 or v >= d[b]) continue;
                d[b] = v, p[b] = a, e[b] = i;
                pq.push({v, b});
            }
        }
        return d[t] != inf;
    }

    pair<int, int> cost_flow(int s, int t, int k = inf) {
        vector<vector<pair<int, int>>> adj(n);
        for (int a = 0; a < n; ++a) {
            for (auto [b, i, w, c, o] : g[a]) if (w > 0) {
                adj[a].push_back({b, c});
            }
        }
        h = spfa(s, adj);
        if (h.empty()) return {-1, -1};
        int flow = 0, cost = 0;
        while (flow < k and dijkstra(s, t)) {
            for (int a = 0; a < n; ++a) if (d[a] != inf) h[a] += d[a];
            int push = k - flow;
            for (int a = t; a != s; a = p[a]) push = min(push, g[p[a]][e[a]].w);
            for (int a = t; a != s; a = p[a]) {
                edge &x = g[p[a]][e[a]];
                x.w -= push, g[a][x.i].w += push;
                cost += push * x.c;
            }
            flow += push;
        }
        return {flow, cost};
    }

    vector<pair<int, int>> saturated_edges() {
        vector<pair<int, int>> edges;
        for (int a = 0; a < n; ++a) {
            for (auto [b, i, w, c, o] : g[a]) if (w == 0 and o) edges.push_back({a, b});
        }
        return edges;
    }
};
