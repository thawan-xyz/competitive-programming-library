struct merge_sort_tree {
    int size;
    array<array<T>> tree;

    merge_sort_tree(int n): size(n), tree(4 * size) {}

    void build(array<T> &base, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        if (left == right) {
            tree[node] = {base[left]};
        } else {
            int middle = (left + right) / 2;
            build(base, node << 1, left, middle);
            build(base, (node << 1) | 1, middle + 1, right);
            tree[node].resize(tree[node << 1].size() + tree[(node << 1) | 1].size());
            merge(tree[node << 1].begin(), tree[node << 1].end(), tree[(node << 1) | 1].begin(), tree[(node << 1) | 1].end(), tree[node].begin());
        }
    }

    int query(T value, int i, int j, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        if (i <= left and j >= right) {
            return upper_bound(tree[node].begin(), tree[node].end(), value) - tree[node].begin();
        } else {
            int answer = 0;
            int middle = (left + right) / 2;
            if (i <= middle) {
                answer += query(value, i, j, node << 1, left, middle);
            }
            if (j > middle) {
                answer += query(value, i, j, (node << 1) | 1, middle + 1, right);
            }
            return answer;
        }
    }
};
