struct flow {
    struct edge {
        int t, w, i;
    };

    int n;
    array<array<edge>> g;
    array<int> f, h, c;
    array<bool> s;
    priority_queue<pair<int, int>> q;

    flow(int n): n(n), g(n), f(n), h(n), c(2 * n), s(n) {}

    void insert(int a, int b, int w) {
        g[a].push_back(edge(b, w, g[b].size()));
        g[b].push_back(edge(a, 0, g[a].size() - 1));
    }

    bool push(int a, edge &e) {
        auto &[b, w, i] = e;

        int p = min(f[a], w);
        if (p and h[a] == h[b] + 1) {
            f[a] -= p;
            f[b] += p;
            w -= p;
            g[b][i].w += p;

            if (not s[b] and f[b]) {
                s[b] = true;
                q.push({h[b], b});
            }
            return true;
        }
        return false;
    }

    void relabel(int a) {
        c[h[a]]--;
        int k = 2 * n;
        for (auto &[b, w, i] : g[a]) if (w) {
            k = min(k, h[b] + 1);
        }
        h[a] = k;
        c[h[a]]++;
    }

    void gap(int k, int s, int t) {
        for (int a = 0; a < n; ++a) if (a != s and a != t) {
            if (h[a] >= k and h[a] <= n) {
                c[h[a]]--;
                h[a] = n + 1;
                c[h[a]]++;

                if (not s[a] and f[a]) {
                    s[a] = true;
                    q.push({h[a], a});
                }
            }
        }
    }

    void drain(int a, int s, int t) {
        s[a] = false;
        while (f[a]) {
            for (auto &e : g[a]) {
                if (push(a, e) and not f[a]) {
                    return;
                }
            }

            if (c[h[a]] == 1) {
                gap(h[a], s, t);
            } else {
                relabel(a);
            }
        }
    }

    int max(int s, int t) {
        c[0] = n - 1;
        h[s] = n;
        c[n] = 1;
        s[s] = s[t] = true;

        for (auto &[b, w, i] : g[s]) if (w) {
            int p = w;
            f[s] -= p;
            f[b] += p;
            w = 0;
            g[b][i].w = p;

            if (b != t) {
                s[b] = true;
                q.push({h[b], b});
            }
        }

        while (not q.empty()) {
            int a = q.top().second; q.pop();
            drain(a, s, t);
        }

        return f[t];
    }
};
