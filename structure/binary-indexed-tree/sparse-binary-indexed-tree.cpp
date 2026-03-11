struct sparse_binary_indexed_tree {
    int n;
    vector<int> is;
    vector<vector<int>> js;
    vector<binary_indexed_tree> tree;

    void compress(vector<int> &a) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int id(vector<int> &a, int i) {
        return lower_bound(a.begin(), a.end(), i) - a.begin();
    }

    sparse_binary_indexed_tree(vector<tuple<char, int, int>> &q) {
        for (auto [t, i, j] : q) is.push_back(i);
        compress(is);
        n = is.size();

        js.resize(n + 1);
        for (auto [t, i, j] : q) {
            if (t == 'u') for (i = id(is, i) + 1; i <= n; i += i & -i) js[i].push_back(j);
            else if (t == 'p') for (i = id(is, i) + 1; i > 0; i -= i & -i) js[i].push_back(j);
        }

        tree.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            compress(js[i]);
            tree[i] = binary_indexed_tree(js[i].size());
        }
    }

    void update(int i, int j, int x) {
        for (i = id(is, i) + 1; i <= n; i += i & -i) tree[i].update(id(js[i], j), x);
    }

    int prefix(int i, int j) {
        int s = 0;
        for (i = id(is, i) + 1; i > 0; i -= i & -i) s += tree[i].prefix(id(js[i], j));
        return s;
    }
};
