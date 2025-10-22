template <typename T, typename F = function<T(const T &, const T &)>>
struct segment_tree {
    int size;
    list<T> tree;
    T neutral;
    F combine;

    segment_tree(list<T> &base, T neutral, F combine): size(base.size()), tree(4 * size), neutral(neutral), combine(move(combine)) {
        build(base);
    }

    void build(list<T> &base, int node = 0, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        if (left == right) {
            tree[node] = base[left];
        } else {
            int middle = (left + right) / 2;
            build(base, (2 * node) + 1, left, middle);
            build(base, (2 * node) + 2, middle + 1, right);
            tree[node] = combine(tree[(2 * node) + 1], tree[(2 * node) + 2]);
        }
    }

    void update(int i, T value, int node = 0, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        if (left == right) {
            tree[node] = value;
        } else {
            int middle = (left + right) / 2;
            if (i <= middle) {
                update(i, value, (2 * node) + 1, left, middle);
            } else {
                update(i, value, (2 * node) + 2, middle + 1, right);
            }
            tree[node] = combine(tree[(2 * node) + 1], tree[(2 * node) + 2]);
        }
    }

    T query(int i, int j, int node = 0, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

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
