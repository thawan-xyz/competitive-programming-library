template <typename T, typename U, typename F, typename G>
struct lazy_segment_tree {
    int size;
    array<T> tree;
    array<U> lazy;
    T neutral;
    U empty;
    F combine;
    G apply;

    lazy_segment_tree(array<T> &a, T neutral, U empty, F combine, G apply): size(a.size()), tree((4 * size) + 1), lazy((4 * size) + 1, empty), neutral(neutral), empty(empty), combine(combine), apply(apply) {
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

    void push(int l, int r, int n) {
        if (lazy[n] == empty) return;

        tree[n] = apply(tree[n], lazy[n], (r - l) + 1);
        if (l != r) {
            lazy[left(n)] = combine(lazy[left(n)], lazy[n]);
            lazy[right(n)] = combine(lazy[right(n)], lazy[n]);
        }
        lazy[n] = empty;
    }

    void update(int queryl, int queryr, T v, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;
        if (queryr < l or queryl > r) return;

        push(l, r, n);
        if (queryl <= l and queryr >= r) {
            lazy[n] = combine(lazy[n], v);
            push(l, r, n);
            return;
        }

        int m = l + (r - l) / 2;
        update(queryl, queryr, v, l, m, left(n));
        update(queryl, queryr, v, m + 1, r, right(n));
        tree[n] = combine(tree[left(n)], tree[right(n)]);
    }

    T query(int queryl, int queryr, int l = 0, int r = -1, int n = 0) {
        if (r < 0) r = size - 1;
        if (l > queryr or r < queryl) return neutral;

        push(l, r, n);
        if (queryl <= l and queryr >= r) return tree[n];

        int m = l + (r - l) / 2;
        return combine(query(queryl, queryr, l, m, left(n)), query(queryl, queryr, m + 1, r, right(n)));
    }
};
