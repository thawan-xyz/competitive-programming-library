struct segment_tree {
    int size;
    array<T> tree;
    T neutral;
    F combine;

    segment_tree(int n): size(n), tree(4 * size) {}

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

    void update(int i, T value, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

        if (left == right) {
            tree[node] = value;
        } else {
            int middle = (left + right) / 2;
            if (i <= middle) {
                update(i, value, node << 1, left, middle);
            } else {
                update(i, value, (node << 1) | 1, middle + 1, right);
            }
            tree[node] = combine(tree[node << 1], tree[(node << 1) | 1]);
        }
    }

    T query(int i, int j, int node = 1, int left = 0, int right = -1) {
        if (right == -1) right = size - 1;

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

struct segment_tree {
    int n;
    array<int> t;

    segment_tree(int n): n(n), t(2 * n) {}

    void build(array<int> &a) {
        for (int i = 0; i < n; ++i) t[i + n] = a[i];
        for (int i = n - 1; i > 0; --i) t[i] = t[i << 1] + t[(i << 1) | 1];
    }

    void update(int i, int v) {
        i += n, t[i] = v;
        while (i > 1) {
            i >>= 1;
            t[i] = t[i << 1] + t[(i << 1) | 1];
        }
    }

    int query(int l, int r) {
        int a = 0;
        l += n, r += n;
        while (l <= r) {
            if (l & 1) a += t[l++];
            if (!(r & 1)) a += t[r--];
            l >>= 1, r >>= 1;
        }
        return a;
    }
};
