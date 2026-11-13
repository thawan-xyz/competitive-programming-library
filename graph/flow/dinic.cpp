// Dinic: maximum flow from s to t, with the minimum cut and the saturated edges
// Time: O(V^2 E), O(E sqrt(V)) with unit capacities | Space: O(V + E)
// Note: after flow, on_cut(a) = a is on the side of s in a minimum cut | saturated_edges = inserted edges a -> b with no capacity left
struct dinic {
    struct edge {
        int b, w, i;
        bool real;
    };

    int n;
    vector<vector<edge>> g;
    vector<int> level, ptr;

    dinic(int n): n(n), g(n), level(n), ptr(n) {}

    void insert(int a, int b, int w, bool undirected = false) {
        int i = g[b].size(), j = g[a].size();
        g[a].push_back({b, w, i, true});
        g[b].push_back({a, undirected ? w : 0, j, undirected});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        vector<int> q = {s};
        for (int i = 0; i < q.size(); ++i) {
            for (auto &e : g[q[i]]) if (e.w > 0 and level[e.b] == -1) level[e.b] = level[q[i]] + 1, q.push_back(e.b);
        }
        return level[t] != -1;
    }

    int dfs(int a, int t, int f) {
        if (a == t) return f;
        int pushed = 0;
        for (int &k = ptr[a]; k < g[a].size(); ++k) {
            auto &[b, w, i, real] = g[a][k];
            if (w == 0 or level[b] != level[a] + 1) continue;
            int d = dfs(b, t, min(f - pushed, w));
            w -= d, g[b][i].w += d, pushed += d;
            if (pushed == f) return f;
        }
        return pushed;
    }

    int flow(int s, int t) {
        int f = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            f += dfs(s, t, inf);
        }
        return f;
    }

    bool on_cut(int a) {
        return level[a] != -1;
    }

    vector<pair<int, int>> saturated_edges() {
        vector<pair<int, int>> res;
        for (int a = 0; a < n; ++a) {
            for (auto &e : g[a]) if (e.real and e.w == 0) res.push_back({a, e.b});
        }
        return res;
    }
};
