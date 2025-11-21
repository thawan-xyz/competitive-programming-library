struct lazy_segment_tree {
    int size;
    array<T> tree;
    array<T> lazy;
    T neutral, empty;
    F combine;
    G apply;

    lazy_segment_tree(int n): size(n), tree(4 * size), lazy(4 * size, empty) {}

    void build(array<T> &base, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        if (left == right) {
            tree[node] = base[left];
        } else {
            int middle = (left + right) / 2;
            build(base, node << 1, left, middle);
            build(base, (node << 1) | 1, middle + 1, right);
            tree[node] = combine(tree[node << 1], tree[(node << 1) | 1]);
        }
    }

    void propagate(int node, int left, int right) {
        if (lazy[node] != empty) {
            tree[node] = apply(tree[node], lazy[node], (right - left) + 1);
            if (left != right) {
                lazy[node << 1] = combine(lazy[node], lazy[node << 1]);
                lazy[(node << 1) | 1] = combine(lazy[node], lazy[(node << 1) | 1]);
            }
            lazy[node] = empty;
        }
    }

    void update(int i, int j, T value, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        propagate(node, left, right);
        if (i <= left and j >= right) {
            lazy[node] = combine(lazy[node], value);
        } else {
            int middle = (left + right) / 2;
            if (i <= middle) {
                update(i, j, value, node << 1, left, middle);
            }
            if (j > middle) {
                update(i, j, value, (node << 1) | 1, middle + 1, right);
            }
            propagate(node << 1, left, middle);
            propagate((node << 1) | 1, middle + 1, right);
            tree[node] = combine(tree[node << 1], tree[(node << 1) | 1]);
        }
    }

    T query(int i, int j, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        propagate(node, left, right);
        if (i <= left and j >= right) {
            return tree[node];
        } else {
            T answer = neutral;
            int middle = (left + right) / 2;
            if (i <= middle) {
                answer = combine(answer, query(i, j, node << 1, left, middle));
            }
            if (j > middle) {
                answer = combine(answer, query(i, j, (node << 1) | 1, middle + 1, right));
            }
            return answer;
        }
    }
};
