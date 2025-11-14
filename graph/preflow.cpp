struct preflow {
    struct edge {
        int to, cap, rev;
    };

    int n;
    array<array<edge>> g;
    array<int> excess;
    array<int> height, count;
    array<bool> active;
    priority_queue<pair<int, int>> q;

    preflow(int n): n(n), g(n), excess(n), height(n), count(2 * n), active(n) {}

    void insert(int a, int b, int c) {
        g[a].push_back(edge(b, c, g[b].size()));
        g[b].push_back(edge(a, 0, g[a].size() - 1));
    }

    void push(int a, edge &e) {
        auto &[b, c, r] = e;

        int send = min(excess[a], c);
        if (height[a] == height[b] + 1 and send) {
            c -= send;
            g[b][r].cap += send;
            excess[a] -= send;
            excess[b] += send;

            if (not active[b] and excess[b]) {
                active[b] = true;
                q.push({height[b], b});
            }
        }
    }

    void relabel(int a) {
        count[height[a]]--;
        int h = 2 * n;
        for (auto &[b, c, r] : g[a]) if (c) {
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

    int flow(int s, int t) {
        count[0] = n - 1;
        height[s] = n;
        count[n] = 1;
        active[s] = active[t] = true;

        for (auto &[b, c, r] : g[s]) if (c) {
            excess[s] -= c;
            excess[b] += c;
            g[b][r].cap = c;
            c = 0;

            if (b != t) {
                active[b] = true;
                q.push({height[b], b});
            }
        }

        while (q.size()) {
            int a = q.top().second;
            active[a] = false;
            q.pop();

            while (excess[a]) {
                for (auto &e : g[a]) {
                    if (not excess[a]) break;
                    push(a, e);
                }

                if (excess[a]) {
                    if (count[height[a]] == 1) {
                        gap(height[a], s, t);
                    } else {
                        relabel(a);
                    }
                }
            }
        }
        
        return excess[t];
    }
};
