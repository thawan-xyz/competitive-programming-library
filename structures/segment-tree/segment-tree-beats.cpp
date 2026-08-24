// Segment Tree Beats: advanced range updates via condition pruning
// Time: update amortized O(log^2 N), query O(log N) | Space: O(N)
// Note: supports sum, add, chmin, chmax and mod over a range
struct segment_tree_beats {
private:
    struct node {
        int sum, lazy;
        int max1, max2, maxc;
        int min1, min2, minc;
    };

    int n;
    vector<node> tree;

    void push_up(int p) {
        int l = 2 * p, r = 2 * p + 1;
        tree[p].sum = tree[l].sum + tree[r].sum;

        if (tree[l].max1 == tree[r].max1) {
            tree[p].max1 = tree[l].max1;
            tree[p].max2 = max(tree[l].max2, tree[r].max2);
            tree[p].maxc = tree[l].maxc + tree[r].maxc;
        } else if (tree[l].max1 > tree[r].max1) {
            tree[p].max1 = tree[l].max1;
            tree[p].max2 = max(tree[l].max2, tree[r].max1);
            tree[p].maxc = tree[l].maxc;
        } else {
            tree[p].max1 = tree[r].max1;
            tree[p].max2 = max(tree[l].max1, tree[r].max2);
            tree[p].maxc = tree[r].maxc;
        }

        if (tree[l].min1 == tree[r].min1) {
            tree[p].min1 = tree[l].min1;
            tree[p].min2 = min(tree[l].min2, tree[r].min2);
            tree[p].minc = tree[l].minc + tree[r].minc;
        } else if (tree[l].min1 < tree[r].min1) {
            tree[p].min1 = tree[l].min1;
            tree[p].min2 = min(tree[l].min2, tree[r].min1);
            tree[p].minc = tree[l].minc;
        } else {
            tree[p].min1 = tree[r].min1;
            tree[p].min2 = min(tree[l].min1, tree[r].min2);
            tree[p].minc = tree[r].minc;
        }
    }

    void apply_add(int p, int l, int r, int v) {
        tree[p].sum += v * (r - l + 1);
        tree[p].max1 += v;
        if (tree[p].max2 != -inf) tree[p].max2 += v;
        tree[p].min1 += v;
        if (tree[p].min2 != inf) tree[p].min2 += v;
        tree[p].lazy += v;
    }

    void apply_min(int p, int v) {
        if (v >= tree[p].max1) return;
        tree[p].sum -= (tree[p].max1 - v) * tree[p].maxc;
        if (tree[p].min1 == tree[p].max1) tree[p].min1 = v;
        if (tree[p].min2 == tree[p].max1) tree[p].min2 = v;
        tree[p].max1 = v;
    }

    void apply_max(int p, int v) {
        if (v <= tree[p].min1) return;
        tree[p].sum += (v - tree[p].min1) * tree[p].minc;
        if (tree[p].max1 == tree[p].min1) tree[p].max1 = v;
        if (tree[p].max2 == tree[p].min1) tree[p].max2 = v;
        tree[p].min1 = v;
    }

    void push_down(int p, int l, int r) {
        int m = (l + r) / 2;
        int left = 2 * p, right = 2 * p + 1;

        if (tree[p].lazy != 0) {
            apply_add(left, l, m, tree[p].lazy);
            apply_add(right, m + 1, r, tree[p].lazy);
            tree[p].lazy = 0;
        }

        apply_min(left, tree[p].max1);
        apply_min(right, tree[p].max1);

        apply_max(left, tree[p].min1);
        apply_max(right, tree[p].min1);
    }

    void build(const vector<int> &a, int p, int l, int r) {
        tree[p].lazy = 0;
        if (l == r) {
            tree[p].sum = tree[p].max1 = tree[p].min1 = a[l];
            tree[p].maxc = tree[p].minc = 1;
            tree[p].max2 = -inf;
            tree[p].min2 = inf;
        } else {
            int m = (l + r) / 2;
            build(a, 2 * p, l, m);
            build(a, 2 * p + 1, m + 1, r);
            push_up(p);
        }
    }

    void update_add(int ql, int qr, int v, int p, int l, int r) {
        if (ql <= l and r <= qr) {
            apply_add(p, l, r, v);
            return;
        }
        push_down(p, l, r);
        int m = (l + r) / 2;
        if (ql <= m) update_add(ql, qr, v, 2 * p, l, m);
        if (qr > m) update_add(ql, qr, v, 2 * p + 1, m + 1, r);
        push_up(p);
    }

    void update_min(int ql, int qr, int v, int p, int l, int r) {
        if (v >= tree[p].max1) return;
        if (ql <= l and r <= qr and v > tree[p].max2) {
            apply_min(p, v);
            return;
        }
        push_down(p, l, r);
        int m = (l + r) / 2;
        if (ql <= m) update_min(ql, qr, v, 2 * p, l, m);
        if (qr > m) update_min(ql, qr, v, 2 * p + 1, m + 1, r);
        push_up(p);
    }

    void update_max(int ql, int qr, int v, int p, int l, int r) {
        if (v <= tree[p].min1) return;
        if (ql <= l and r <= qr and v < tree[p].min2) {
            apply_max(p, v);
            return;
        }
        push_down(p, l, r);
        int m = (l + r) / 2;
        if (ql <= m) update_max(ql, qr, v, 2 * p, l, m);
        if (qr > m) update_max(ql, qr, v, 2 * p + 1, m + 1, r);
        push_up(p);
    }

    void update_mod(int ql, int qr, int v, int p, int l, int r) {
        if (ql <= l and r <= qr) {
            if (tree[p].max1 < v) return;
            if (tree[p].min1 == tree[p].max1) {
                apply_add(p, l, r, (tree[p].max1 % v) - tree[p].max1);
                return;
            }
        }
        push_down(p, l, r);
        int m = (l + r) / 2;
        if (ql <= m) update_mod(ql, qr, v, 2 * p, l, m);
        if (qr > m) update_mod(ql, qr, v, 2 * p + 1, m + 1, r);
        push_up(p);
    }

    int query_sum(int ql, int qr, int p, int l, int r) {
        if (ql <= l and r <= qr) return tree[p].sum;
        push_down(p, l, r);
        int m = (l + r) / 2;
        int ans = 0;
        if (ql <= m) ans += query_sum(ql, qr, 2 * p, l, m);
        if (qr > m) ans += query_sum(ql, qr, 2 * p + 1, m + 1, r);
        return ans;
    }

public:
    segment_tree_beats(int n) : n(n), tree(4 * n) {}

    segment_tree_beats(const vector<int> &a) : n(a.size()), tree(4 * n) {
        build(a, 1, 0, n - 1);
    }

    void update_add(int l, int r, int v) {
        update_add(l, r, v, 1, 0, n - 1);
    }

    void update_min(int l, int r, int v) {
        update_min(l, r, v, 1, 0, n - 1);
    }

    void update_max(int l, int r, int v) {
        update_max(l, r, v, 1, 0, n - 1);
    }

    void update_mod(int l, int r, int v) {
        update_mod(l, r, v, 1, 0, n - 1);
    }

    int query_sum(int l, int r) {
        return query_sum(l, r, 1, 0, n - 1);
    }
};
