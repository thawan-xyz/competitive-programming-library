struct min_cost_flow {
    int n;
    vector<vector<array<int, 4>>> g;
    vector<int> d, h, p, e;

    min_cost_flow(int n): n(n), g(n), d(n), h(n), p(n), e(n) {}

    void insert_edge(int a, int b, int capacity, int cost) {
        g[a].push_back({b, g[b].size(), capacity, cost});
        g[b].push_back({a, g[a].size() - 1, 0, -cost});
    }

    bool dijkstra(int s, int t) {
        fill(d.begin(), d.end(), inf);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        d[s] = 0;
        pq.emplace(0, s);
        while (pq.size()) {
            auto [x, a] = pq.top(); pq.pop();
            if (d[a] < x) continue;

            for (int i = 0; i < g[a].size(); ++i) {
                auto &[b, j, capacity, cost] = g[a][i];
                if (capacity <= 0) continue;

                int w = d[a] + cost + h[a] - h[b];
                if (w < d[b]) {
                    d[b] = w;
                    p[b] = a;
                    e[b] = i;
                    pq.emplace(d[b], b);
                }
            }
        }
        return d[t] != inf;
    }

    pair<int, int> min_cost_k_flow(int s, int t, int k = inf) {
        int flow = 0, cost = 0;
        fill(h.begin(), h.end(), 0);
        while (flow < k and dijkstra(s, t)) {
            for (int a = 0; a < n; ++a) if (d[a] != inf) {
                h[a] += d[a];
            }

            int push = k - flow;
            for (int a = t; a != s; a = p[a]) {
                int b = p[a], i = e[a];
                push = min(push, g[b][i][2]);
            }
            for (int a = t; a != s; a = p[a]) {
                int b = p[a], i = e[a], j = g[b][i][1];
                g[b][i][2] -= push;
                g[a][j][2] += push;
                cost += g[b][i][3] * push;
            }
            flow += push;
        }
        return {flow, cost};
    }
};
