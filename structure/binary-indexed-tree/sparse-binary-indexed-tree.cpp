struct sparse_binary_indexed_tree {
    struct query {
        char t;
        int i, j;
    };

    int n;
    list<int> is;
    list<list<int>> js;
    list<binary_indexed_tree> tree;

    static int lsb(int i) {
        return i & -i;
    }

    static void compress(list<int> &a) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int id(int i) {
        return lower_bound(is.begin(), is.end(), i) - is.begin();
    }

    int id(int i, int j) {
        return lower_bound(js[i].begin(), js[i].end(), j) - js[i].begin();
    }

    sparse_binary_indexed_tree(list<query> &q) {
        for (auto &[t, i, j] : q) {
            is.push_back(i);
        }
        compress(is);

        n = is.size();
        js.resize(n + 1);
        for (auto &[t, i, j] : q) {
            i = id(i) + 1;
            if (t == '0') {
                while (i > 0) {
                    js[i].push_back(j);
                    i -= lsb(i);
                }
            } else {
                while (i <= n) {
                    js[i].push_back(j);
                    i += lsb(i);
                }
            }
        }

        tree.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            compress(js[i]);
            tree[i] = binary_indexed_tree(js[i].size());
        }
    }

    int prefix(int i, int j) {
        int s = 0;
        i = id(i) + 1;
        while (i > 0) {
            s += tree[i].prefix(id(i, j));
            i -= lsb(i);
        }
        return s;
    }

    void modify(int i, int j, int d) {
        i = id(i) + 1;
        while (i <= n) {
            tree[i].modify(id(i, j), d);
            i += lsb(i);
        }
    }
};
