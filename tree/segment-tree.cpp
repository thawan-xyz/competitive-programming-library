template <typename T, typename F>
struct segment_tree {
    int size;
    array<T> tree;
    T neutral;
    F combine;

    segment_tree(array<T> &a, T neutral, F combine): size(a.size()), tree((4 * size) + 1), neutral(neutral), combine(combine) {
        build(a);
    }

    void build(array<T> &a, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;

        if (l == r) {
            tree[n] = a[l];
        } else {
            int m = (l + r) / 2;
            build(a, l, m, (2 * n) + 1), build(a, m + 1, r, (2 * n) + 2);
            tree[n] = combine(tree[(2 * n) + 1], tree[(2 * n) + 2]);
        }
    }

    void update(int i, T v, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;
        if (i < l or i > r) return;

        if (l == r) {
            tree[n] = v;
        } else {
            int m = (l + r) / 2;
            update(i, v, l, m, (2 * n) + 1), update(i, v, m + 1, r, (2 * n) + 2);
            tree[n] = combine(tree[(2 * n) + 1], tree[(2 * n) + 2]);
        }
    }

    T query(int queryl, int queryr, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;
        if (l > queryr or r < queryl) return neutral;

        if (queryl <= l and queryr >= r) {
            return tree[n];
        } else {
            int m = (l + r) / 2;
            return combine(query(queryl, queryr, l, m, (2 * n) + 1), query(queryl, queryr, m + 1, r, (2 * n) + 2));
        }
    }
};
