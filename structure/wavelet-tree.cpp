struct wavelet_tree {
private:
    struct node {
        int l, r, low, high;
        array<int> pref;

        node(int low = 0, int high = 0, int size = 0): l(0), r(0), low(low), high(high), pref(size + 1) {}
    };

    int root;
    array<node> tree;

    int build(array<int> &a, int low, int high) {
        int p = tree.size();
        tree.push_back(node(low, high, a.size()));

        if (low == high) {
            for (int i = 0; i < a.size(); ++i) {
                tree[p].pref[i + 1] = tree[p].pref[i] + 1;
            }
        } else {
            int mid = (low + high) / 2;
            array<int> l; l.reserve(a.size());
            array<int> r; r.reserve(a.size());

            for (int i = 0; i < a.size(); ++i) {
                tree[p].pref[i + 1] = tree[p].pref[i];
                if (a[i] <= mid) {
                    tree[p].pref[i + 1] += 1;
                    l.push_back(a[i]);
                } else {
                    r.push_back(a[i]);
                }
            }

            if (l.size()) tree[p].l = build(l, low, mid);
            if (r.size()) tree[p].r = build(r, mid + 1, high);
        }
        return p;
    }

    int count_less_equal(int ql, int qr, int x, int p) {
        if (not p or (tree[p].low > x or ql > qr)) return 0;

        if (tree[p].high <= x) return (qr - ql) + 1;

        int prev = tree[p].pref[ql];
        int curr = tree[p].pref[qr + 1] - tree[p].pref[ql];

        return count_less_equal(prev, (curr + prev) - 1, x, tree[p].l) + count_less_equal(ql - prev, qr - (prev + curr), x, tree[p].r);
    }

    int kth(int ql, int qr, int k, int p) {
        if (tree[p].low == tree[p].high) return tree[p].low;

        int prev = tree[p].pref[ql];
        int curr = tree[p].pref[qr + 1] - tree[p].pref[ql];

        if (k < curr) {
            return kth(prev, (curr + prev) - 1, k, tree[p].l);
        } else {
            return kth(ql - prev, qr - (curr + prev), k - curr, tree[p].r);
        }
    }

public:
    wavelet_tree(array<int> &a): tree(1) {
        tree.reserve(2 * a.size());
        root = build(a, *min_element(a.begin(), a.end()), *max_element(a.begin(), a.end()));
    }

    int count_less_equal(int l, int r, int x) {
        return count_less_equal(l, r, x, root);
    }

    int kth(int l, int r, int k) {
        return kth(l, r, k, root);
    }
};
