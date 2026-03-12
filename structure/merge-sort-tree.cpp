struct merge_sort_tree {
    int n;
    vector<int> a;
    vector<ordered_set<pair<int, int>>> tree;

    merge_sort_tree(vector<int> &a): n(a.size()), a(a), tree(2 * n) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + n; j > 0; j >>= 1) {
                tree[j].insert({a[i], i});
            }
        }
    }

    void update(int i, int x) {
        for (int j = i + n; j > 0; j >>= 1) {
            tree[j].erase({a[i], i});
            tree[j].insert({x, i});
        }
        a[i] = x;
    }

    int query(int i, int j, int k) {
        int c = 0;
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) c += tree[i++].order_of_key({k + 1, 0});
            if (j & 1) c += tree[--j].order_of_key({k + 1, 0});
        }
        return c;
    }
};
