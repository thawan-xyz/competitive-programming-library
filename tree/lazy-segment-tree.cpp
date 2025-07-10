template <typename T, typename F = function<T(const T &, const T &)>, typename G = function<T(const T &, const T &, const int &)>>
struct lazy_segment_tree {
    int size;
    array<T> tree;
    array<T> lazy;
    T neutral, empty;
    F combine;
    G apply;

    lazy_segment_tree(array<T> &base, T neutral, T empty, F combine, G apply): size(base.size()), tree(4 * size), lazy(4 * size, empty), neutral(neutral), empty(empty), combine(combine), apply(apply) {
        build(base);
    }

    void build(array<T> &base, int node = 0, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        if (left == right) {
            tree[node] = base[left];
        } else {
            int middle = (left + right) / 2;
            build(a, (2 * node) + 1, left, middle);
            build(a, (2 * node) + 2, middle + 1, right);
            tree[node] = combine(tree[(2 * node) + 1], tree[(2 * node) + 2]);
        }
    }

    void propagate(int node, int left, int right) {
        if (lazy[node] != empty) {
            tree[node] = apply(tree[node], lazy[node], (right - left) + 1);
            if (left != right) {
                lazy[(2 * node) + 1] = combine(lazy[node], lazy[(2 * node) + 1]);
                lazy[(2 * node) + 2] = combine(lazy[node], lazy[(2 * node) + 2]);
            }
            lazy[node] = empty;
        }
    }

    void update(int i, int j, T value, int node = 0, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        propagate(node, left, right);
        if (i <= left and j >= right) {
            lazy[node] = combine(lazy[node], value);
        } else {
            int middle = (left + right) / 2;
            if (i <= middle) {
                update(i, j, value, (2 * node) + 1, left, middle);
            }
            if (j > middle) {
                update(i, j, value, (2 * node) + 2, middle + 1, right);
            }
            propagate((2 * node) + 1, left, middle);
            propagate((2 * node) + 2, middle + 1, right);
            tree[node] = combine(tree[(2 * node) + 1], tree[(2 * node) + 2]);
        }
    }

    T query(int i, int j, int node = 0, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        propagate(node, left, right);
        if (i <= left and j >= right) {
            return tree[node];
        } else {
            T answer = neutral;
            int middle = (left + right) / 2;
            if (i <= middle) {
                answer = combine(answer, query(i, j, (2 * node) + 1, left, middle));
            }
            if (j > middle) {
                answer = combine(answer, query(i, j, (2 * node) + 2, middle + 1, right));
            }
            return answer;
        }
    }
};
