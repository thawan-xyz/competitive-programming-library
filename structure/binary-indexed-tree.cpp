struct binary_indexed_tree {
    int n;
    list<int> tree;

    static int lsb(int i) {
        return i & -i;
    }

    binary_indexed_tree(int n): n(n), tree(n + 1) {}

    void build(list<int> &a) {
        for (int i = 0; i < n; ++i) modify(i, a[i]);
    }

    void modify(int i, int d) {
        i += 1;
        while (i <= n) {
            tree[i] += d;
            i += lsb(i);
        }
    }

    int prefix(int i) {
        int s = 0;
        i += 1;
        while (i > 0) {
            s += tree[i];
            i -= lsb(i);
        }
        return s;
    }

    int query(int i, int j) {
        return prefix(j) - prefix(i - 1);
    }
};
