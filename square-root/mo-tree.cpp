// Mo's Algorithm on Trees: offline path queries on vertex values
// Time: O((N + Q) sqrt N) | Space: O(N + Q)
// Note: requires hilbert (mo) | q elements: {u, v, lca(u, v)} | implement 'insert', 'remove' and 'curr' like in mo
vector<int> mo_tree(vector<vector<int>> &g, vector<int> &a, vector<array<int, 3>> &q) {
    int n = g.size();
    vector<int> tin(n), tout(n), order;
    auto dfs = [&](auto &self, int u, int p) -> void {
        tin[u] = order.size();
        order.push_back(u);
        for (int v : g[u]) if (v != p) self(self, v, u);
        tout[u] = order.size();
        order.push_back(u);
    };
    dfs(dfs, 0, -1);

    vector<array<int, 5>> qs;
    for (int k = 0; k < q.size(); ++k) {
        auto [u, v, p] = q[k];
        if (tin[u] > tin[v]) swap(u, v);
        int l = p == u ? tin[u] : tout[u], r = tin[v];
        qs.push_back({hilbert(l, r), l, r, p == u ? -1 : p, k});
    }
    sort(qs.begin(), qs.end());

    int curr = 0;
    auto insert = [&](int x) -> void {};
    auto remove = [&](int x) -> void {};

    vector<bool> on(n);
    auto toggle = [&](int u) -> void {
        if (on[u]) remove(a[u]);
        else insert(a[u]);
        on[u] = not on[u];
    };

    vector<int> ans(q.size());
    int i = 0, j = -1;
    for (auto [h, l, r, p, id] : qs) {
        while (i > l) toggle(order[--i]);
        while (j < r) toggle(order[++j]);
        while (i < l) toggle(order[i++]);
        while (j > r) toggle(order[j--]);
        if (p != -1) insert(a[p]);
        ans[id] = curr;
        if (p != -1) remove(a[p]);
    }
    return ans;
}
