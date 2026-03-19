struct merge_sort_tree {
    int n;
    vector<vector<int>> tree;

    merge_sort_tree(vector<int> &a): n(a.size()), tree(2 * n) {
        for (int i = 0; i < n; ++i) tree[i + n] = {a[i]};
        for (int i = n - 1; i > 0; --i) merge(tree[i << 1].begin(), tree[i << 1].end(), tree[(i << 1) | 1].begin(), tree[(i << 1) | 1].end(), back_inserter(tree[i]));
    }

    int query(int i, int j, int x) {
        int c = 0;
        for (i += n, j += n + 1; i < j; i >>= 1, j >>= 1) {
            if (i & 1) c += upper_bound(tree[i].begin(), tree[i].end(), x) - tree[i].begin(), i++;
            if (j & 1) --j, c += upper_bound(tree[j].begin(), tree[j].end(), x) - tree[j].begin();
        }
        return c;
    }
};
