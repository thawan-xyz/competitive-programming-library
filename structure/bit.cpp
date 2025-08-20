template <typename T>
struct bit {
    int n;
    array<T> tree;

    static int lsb(int i) {
        return i & -i;
    }

    bit(array<T> &base): n(base.size()), tree(n + 1) {
        for (int i = 0; i < n; ++i) update(i, base[i]);
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
        if (l > r) return 0;
        return prefix(r) - prefix(l - 1);
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
};
