template <typename T, typename F>
struct segment_tree {
    int size;
    array<T> tree;
    T neutral;
    F combine;

    segment_tree(array<T> &a, T neutral, F combine): size(a.size()), tree((4 * size) + 1), neutral(neutral), combine(combine) {
        build(a);
    }

    int left(int n) {
        return (n << 1) + 1;
    }

    int right(int n) {
        return (n << 1) + 2;
    }

    void build(array<T> &a, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;

        if (l == r) {
            tree[n] = a[l];
            return;
        }

        int m = l + (r - l) / 2;
        build(a, l, m, left(n));
        build(a, m + 1, r, right(n));
        tree[n] = combine(tree[left(n)], tree[right(n)]);
    }

    void update(int i, T v, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;
        if (i < l or i > r) return;

        if (l == r) {
            tree[n] = v;
            return;
        }

        int m = l + (r - l) / 2;
        update(i, v, l, m, left(n));
        update(i, v, m + 1, r, right(n));
        tree[n] = combine(tree[left(n)], tree[right(n)]);
    }

    T query(int queryl, int queryr, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;
        if (l > queryr or r < queryl) return neutral;

        if (queryl <= l and queryr >= r) return tree[n];

        int m = l + (r - l) / 2;
        return combine(query(queryl, queryr, l, m, left(n)), query(queryl, queryr, m + 1, r, right(n)));
    }
};
