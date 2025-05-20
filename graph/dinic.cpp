struct edge {
    int b;
    long capacity, flow;

    edge(int b, long c): b(b), capacity(c), flow(0) {}
};

struct dinic {
    long inf = 1e18;
    int v, e;
    array<edge> edges;
    array<array<int>> graph;
    array<int> level, last;

    dinic(int v): v(v), e(0), graph(v), level(v), last(v) {}

    void add(int a, int b, long w, bool directed = true) {
        if (a == b) return;

        edges.emplace_back(b, w);
        graph[a].push_back(e++);
        edges.emplace_back(a, directed ? 0 : w);
        graph[b].push_back(e++);
    }

    bool bfs(int s, int t) {
        ranges::fill(level, -1);
        queue<int> q; q.push(s);
        level[s] = 0;

        while (q.size() > 0) {
            int a = q.front(); q.pop();
            if (a == t) break;
            for (int i : graph[a]) {
                if (edges[i].capacity == edges[i].flow or level[edges[i].b] != -1) continue;

                level[edges[i].b] = level[a] + 1;
                q.push(edges[i].b);
            }
        }
        return level[t] != -1;
    }

    long dfs(int a, int t, long f) {
        if (a == t or f == 0) return f;

        for (int &i = last[a]; i < graph[a].size(); ++i) {
            int j = graph[a][i];
            int b = edges[j].b;
            if (level[a] + 1 != level[b]) continue;
            if (long p = dfs(b, t, min(f, edges[j].capacity - edges[j].flow))) {
                edges[j].flow += p;
                edges[j ^ 1].flow -= p;
                return p;
            }
        }
        return 0;
    }

    long flow(int s, int t) {
        long f = 0;
        while (bfs(s, t)) {
            ranges::fill(last, 0);
            while (long p = dfs(s, t, inf)) {
                f += p;
            }
        }
        return f;
    }
};
