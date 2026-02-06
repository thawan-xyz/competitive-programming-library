struct cost_flow {
    struct edge {
        int to;
        int rev;
        int cap;
        int cost;
    };

    int n;
    list<list<edge>> g;
    list<int> dist, pot;
    list<pair<int, int>> par;

    cost_flow(int n): n(n), g(n), dist(n), pot(n), par(n) {}

    void insert_edge(int a, int b, int cap, int cost) {
        edge i = {b, g[b].size(), cap, cost};
        edge j = {a, g[a].size(), 0, -cost};
        g[a].push_back(i);
        g[b].push_back(j);
    }

    bool dijkstra(int s, int t) {
        fill(dist.begin(), dist.end(), inf);

        priority_queue<pair<int, int>, list<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[s] = 0;
        pq.push({0, s});
        while (pq.size()) {
            auto [d, a] = pq.top(); pq.pop();
            if (dist[a] != d) continue;

            for (int i = 0; i < g[a].size(); ++i) {
                auto &[b, j, cap, cost] = g[a][i];
                if (cap <= 0) continue;

                int e = d + cost + pot[a] - pot[b];
                if (e < dist[b]) {
                    dist[b] = e;
                    par[b] = {a, i};
                    pq.push({dist[b], b});
                }
            }
        }
        return dist[t] != inf;
    }

    pair<int, int> min_cost_k_flow(int s, int t, int k) {
        int flow = 0, cost = 0;
        fill(pot.begin(), pot.end(), 0);
        while (flow < k and dijkstra(s, t)) {
            for (int a = 0; a < n; ++a) if (dist[a] != inf) {
                pot[a] += dist[a];
            }

            int push = k - flow;
            for (int a = t; a != s; a = par[a].first) {
                auto &[p, i] = par[a];
                push = min(push, g[p][i].cap);
            }
            for (int a = t; a != s; a = par[a].first) {
                auto &[p, i] = par[a];
                int j = g[p][i].rev;
                g[p][i].cap -= push;
                g[a][j].cap += push;
                cost += g[p][i].cost * push;
            }
            flow += push;
        }
        return {flow, cost};
    }
};
