template <typename T>
struct merge_sort_tree {
    int size;
    list<list<T>> tree;

    merge_sort_tree(list<T> &base): size(base.size()), tree(4 * size) {
        build(base);
    }

    void build(list<T> &base, int node = 0, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        if (left == right) {
            tree[node] = {base[left]};
        } else {
            int middle = (left + right) / 2;
            build(base, (2 * node) + 1, left, middle);
            build(base, (2 * node) + 2, middle + 1, right);
            tree[node].resize(tree[(2 * node) + 1].size() + tree[(2 * node) + 2].size());
            merge(tree[(2 * node) + 1].begin(), tree[(2 * node) + 1].end(), tree[(2 * node) + 2].begin(), tree[(2 * node) + 2].end(), tree[node].begin());
        }
    }

    int query(int i, int j, T value, int node = 0, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        if (i <= left and j >= right) {
            return upper_bound(tree[node].begin(), tree[node].end(), value) - tree[node].begin();
        } else {
            int answer = 0;
            int middle = (left + right) / 2;
            if (i <= middle) {
                answer += query(i, j, value, (2 * node) + 1, left, middle);
            }
            if (j > middle) {
                answer += query(i, j, value, (2 * node) + 2, middle + 1, right);
            }
            return answer;
        }
    }
};
