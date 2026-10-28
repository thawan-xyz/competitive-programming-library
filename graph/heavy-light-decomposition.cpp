// Heavy-Light Decomposition: splits a path into O(log N) ranges of positions for an external structure
// Time: O(N) build, O(log N) per path | Space: O(N)
// Usage: hld h(g, false) values on vertices, hld h(g, true) values on edges | vertex v is at h.id[v], edge u-v at h.edge(u, v)
struct hld {
    int t;
    bool e;
    vector<int> p, h, s, id;

    hld(vector<vector<int>> &g, bool e): t(0), e(e) {
        int n = g.size();
        p.resize(n);
        h.resize(n);
        s.resize(n);
        id.resize(n);
        for (int i = 0; i < n; ++i) if (s[i] == 0) {
            p[i] = h[i] = i;
            dfs(i, g);
            decompose(i, g);
        }
    }

    void dfs(int a, vector<vector<int>> &g) {
        s[a] = 1;
        for (int &b : g[a]) if (b != p[a]) {
            p[b] = a;
            dfs(b, g);
            s[a] += s[b];
            if (g[a][0] == p[a] or s[b] > s[g[a][0]]) {
                swap(b, g[a][0]);
            }
        }
    }

    void decompose(int a, vector<vector<int>> &g) {
        id[a] = t++;
        for (int b : g[a]) if (b != p[a]) {
            h[b] = (b == g[a][0] ? h[a] : b);
            decompose(b, g);
        }
    }

    int edge(int u, int v) {
        return max(id[u], id[v]);
    }

    vector<tuple<int, int, bool>> path(int a, int b) {
        vector<tuple<int, int, bool>> up, down;
        while (h[a] != h[b]) {
            if (id[h[a]] > id[h[b]]) {
                up.push_back({id[h[a]], id[a], true});
                a = p[h[a]];
            } else {
                down.push_back({id[h[b]], id[b], false});
                b = p[h[b]];
            }
        }
        if (id[a] > id[b]) {
            up.push_back({id[b] + e, id[a], true});
        } else if (id[a] + e <= id[b]) {
            down.push_back({id[a] + e, id[b], false});
        }
        up.insert(up.end(), down.rbegin(), down.rend());
        return up;
    }

    tuple<int, int> subtree(int v) {
        return {id[v] + e, id[v] + s[v] - 1};
    }
};
