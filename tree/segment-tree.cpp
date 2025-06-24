struct segment_tree {
    int size;
    array<int> tree;

    segment_tree(array<int> &a): size(a.size()), tree((4 * size) + 1) {
        build(a);
    }

    void build(array<int> &a, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;

        if (l == r) {
            tree[n] = a[l];
        } else {
            int m = (l + r) / 2;
            build(a, l, m, (2 * n) + 1), build(a, m + 1, r, (2 * n) + 2);
            tree[n] = tree[(2 * n) + 1] + tree[(2 * n) + 2];
        }
    }

    void update(int i, int v, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;
        if (i < l or i > r) return;

        if (l == r) {
            tree[n] = v;
        } else {
            int m = (l + r) / 2;
            update(i, v, l, m, (2 * n) + 1), update(i, v, m + 1, r, (2 * n) + 2);
            tree[n] = tree[(2 * n) + 1] + tree[(2 * n) + 2];
        }
    }

    int query(int queryl, int queryr, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;
        if (l > queryr or r < queryl) return 0;

        if (queryl <= l and queryr >= r) {
            return tree[n];
        } else {
            int m = (l + r) / 2;
            return query(queryl, queryr, l, m, (2 * n) + 1) + query(queryl, queryr, m + 1, r, (2 * n) + 2);
        }
    }
};
