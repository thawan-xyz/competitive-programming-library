// Merge Sort Tree: counts the values <= x in a range, with each node keeping its range sorted
// Time: O(N log N) build, O(log^2 N) query | Space: O(N log N)
struct merge_sort_tree {
    int n;
    vector<vector<int>> tree;

    merge_sort_tree(vector<int> &a): n(a.size()), tree(4 * n) {
        auto rec = [&](auto &self, int p, int l, int r) -> void {
            if (l == r) return void(tree[p] = {a[l]});
            int m = l + (r - l) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m + 1, r);
            ranges::merge(tree[2 * p], tree[2 * p + 1], back_inserter(tree[p]));
        };
        rec(rec, 1, 0, n - 1);
    }

    int less_or_equal(int ql, int qr, int x) {
        auto rec = [&](auto &self, int p, int l, int r) -> int {
            if (qr < l or r < ql) return 0;
            if (ql <= l and r <= qr) return ranges::upper_bound(tree[p], x) - tree[p].begin();
            int m = l + (r - l) / 2;
            return self(self, 2 * p, l, m) + self(self, 2 * p + 1, m + 1, r);
        };
        return rec(rec, 1, 0, n - 1);
    }
};
