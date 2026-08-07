// Min Cost K-Flow: successive shortest path with potentials
// Time: O(F * E log V) where F is flow | Space: O(V + E)
// Note: initial costs MUST be >= 0
struct min_cost_k_flow {
    struct edge {
        int b, i, w, c;
        bool o;
    };

    int n;
    vector<vector<edge>> g;
    vector<int> d, h, p, e;

    min_cost_k_flow(int n): n(n), g(n), d(n), h(n), p(n), e(n) {}

    void directed(int a, int b, int w, int c) {
        g[a].emplace_back(b, g[b].size(), w, c, true);
        g[b].emplace_back(a, g[a].size() - 1, 0, -c, false);
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
                auto &[b, j, w, c, o] = g[a][i];
                if (w <= 0) continue;

                int v = d[a] + c + h[a] - h[b];
                if (v < d[b]) {
                    d[b] = v;
                    p[b] = a;
                    e[b] = i;
                    pq.emplace(d[b], b);
                }
            }
        }
        return d[t] != inf;
    }

    pair<int, int> cost_flow(int s, int t, int k = inf) {
        int flow = 0, cost = 0;
        fill(h.begin(), h.end(), 0);
        while (flow < k and dijkstra(s, t)) {
            for (int a = 0; a < n; ++a) if (d[a] != inf) {
                h[a] += d[a];
            }

            int push = k - flow;
            for (int a = t; a != s; a = p[a]) {
                int b = p[a], i = e[a];
                push = min(push, g[b][i].w);
            }
            for (int a = t; a != s; a = p[a]) {
                int b = p[a], i = e[a], j = g[b][i].i;
                g[b][i].w -= push;
                g[a][j].w += push;
                cost += g[b][i].c * push;
            }
            flow += push;
        }
        return {flow, cost};
    }

    vector<pair<int, int>> saturated_edges() {
        vector<pair<int, int>> edges;
        for (int a = 0; a < n; ++a) {
            for (auto &[b, i, w, c, o] : g[a]) if (w == 0 and o) {
                edges.push_back({a, b});
            }
        }
        return edges;
    }
};
