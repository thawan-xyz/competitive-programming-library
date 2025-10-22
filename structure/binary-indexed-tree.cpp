template <typename T>
struct binary_indexed_tree {
    int n;
    list<T> tree;

    static int lsb(int i) {
        return i & -i;
    }

    binary_indexed_tree(list<T> &base): n(base.size()), tree(n + 1) {
        for (int i = 0; i < n; ++i) update(i, base[i]);
    }

    void update(int i, T d) {
        i += 1;
        while (i <= n) {
            tree[i] += d;
            i += lsb(i);
        }
    }

    void set(int i, T v) {
        T d = v - query(i, i);
        update(i, d);
    }

    T prefix(int i) {
        T s = 0;
        i += 1;
        while (i > 0) {
            s += tree[i];
            i -= lsb(i);
        }
        return s;
    }

    T query(int l, int r) {
        return prefix(r) - prefix(l - 1);
    }

    int kth(int k) {
        int i = 0;
        for (int j = 1 << (31 - __builtin_clz(n)); j > 0; j >>= 1) {
            if (i + j <= n and tree[i + j] < k) {
                k -= tree[i + j];
                i += j;
            }
        }
        return i;
    }
};
