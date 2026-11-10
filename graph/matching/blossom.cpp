// Blossom: maximum matching in a general graph, with Edmonds' algorithm
// Time: O(V^3) | Space: O(V + E)
// Note: undirected graph, an edge goes in both lists | returns match[a], the vertex matched with a or -1
vector<int> blossom(vector<vector<int>> &g) {
    int n = g.size();
    vector<int> match(n, -1), p(n), base(n), q;
    vector<bool> used(n), mark(n);

    auto lca = [&](int a, int b) -> int {
        vector<bool> seen(n);
        for (a = base[a]; ; a = base[p[match[a]]]) {
            seen[a] = true;
            if (match[a] == -1) break;
        }
        for (b = base[b]; not seen[b]; b = base[p[match[b]]]);
        return b;
    };

    auto mark_path = [&](int a, int c, int child) {
        while (base[a] != c) {
            mark[base[a]] = mark[base[match[a]]] = true;
            p[a] = child, child = match[a], a = p[match[a]];
        }
    };

    auto find_path = [&](int root) -> int {
        fill(used.begin(), used.end(), false);
        fill(p.begin(), p.end(), -1);
        iota(base.begin(), base.end(), 0);
        used[root] = true, q = {root};
        for (int h = 0; h < q.size(); ++h) {
            int a = q[h];
            for (int b : g[a]) {
                if (base[a] == base[b] or match[a] == b) continue;
                if (b == root or (match[b] != -1 and p[match[b]] != -1)) {
                    int c = lca(a, b);
                    fill(mark.begin(), mark.end(), false);
                    mark_path(a, c, b), mark_path(b, c, a);
                    for (int i = 0; i < n; ++i) if (mark[base[i]]) {
                        base[i] = c;
                        if (not used[i]) used[i] = true, q.push_back(i);
                    }
                } else if (p[b] == -1) {
                    p[b] = a;
                    if (match[b] == -1) return b;
                    used[match[b]] = true, q.push_back(match[b]);
                }
            }
        }
        return -1;
    };

    for (int a = 0; a < n; ++a) {
        for (int b : g[a]) if (a != b and match[a] == -1 and match[b] == -1) match[a] = b, match[b] = a;
    }
    for (int a = 0; a < n; ++a) {
        if (match[a] != -1) continue;
        for (int b = find_path(a); b != -1;) {
            int c = p[b], d = match[c];
            match[b] = c, match[c] = b, b = d;
        }
    }
    return match;
}
