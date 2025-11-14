struct flow {
    struct edge {
        int to, cap, i;
    };

    int n;
    array<array<edge>> g;
    array<int> excess;
    array<int> height, count;
    array<bool> active;
    priority_queue<pair<int, int>> q;

    flow(int n): n(n), g(n), excess(n), height(n), count(2 * n), active(n) {}

    void insert(int a, int b, int c) {
        g[a].push_back(edge(b, c, g[b].size()));
        g[b].push_back(edge(a, 0, g[a].size() - 1));
    }

    bool push(int a, edge &e) {
        auto &[b, c, i] = e;

        int f = min(excess[a], c);
        if (f and height[a] == height[b] + 1) {
            excess[a] -= f;
            excess[b] += f;
            c -= f;
            g[b][i].cap += f;

            if (not active[b] and excess[b]) {
                active[b] = true;
                q.push({height[b], b});
            }
            return true;
        }
        return false;
    }

    void relabel(int a) {
        count[height[a]]--;
        int h = 2 * n;
        for (auto &[b, c, i] : g[a]) if (c) {
            h = min(h, height[b] + 1);
        }
        height[a] = h;
        count[height[a]]++;
    }

    void gap(int h, int s, int t) {
        for (int a = 0; a < n; ++a) if (a != s and a != t) {
            if (height[a] >= h and height[a] <= n) {
                count[height[a]]--;
                height[a] = n + 1;
                count[height[a]]++;

                if (not active[a] and excess[a]) {
                    active[a] = true;
                    q.push({height[a], a});
                }
            }
        }
    }

    void drain(int a, int s, int t) {
        active[a] = false;
        while (excess[a]) {
            for (auto &e : g[a]) {
                if (push(a, e) and not excess[a]) {
                    return;
                }
            }

            if (count[height[a]] == 1) {
                gap(height[a], s, t);
            } else {
                relabel(a);
            }
        }
    }

    int max(int s, int t) {
        count[0] = n - 1;
        height[s] = n;
        count[n] = 1;
        active[s] = active[t] = true;

        for (auto &[b, c, i] : g[s]) if (c) {
            excess[s] -= c;
            excess[b] += c;
            g[b][i].cap = c;
            c = 0;

            if (b != t) {
                active[b] = true;
                q.push({height[b], b});
            }
        }

        while (not q.empty()) {
            int a = q.top().second; q.pop();
            drain(a, s, t);
        }

        return excess[t];
    }
};
