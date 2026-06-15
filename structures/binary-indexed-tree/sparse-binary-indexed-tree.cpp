// Sparse BIT: 2D Binary Indexed Tree with Static Coordinate Compression
// Time: Build O(Q log² Q) | Update/Query O(log² Q) | Space: O(Q log Q)
// Queries: {type, i1, j1, i2, j2} | 'U' = Update, 'Q' = Query
struct sparse_bit {
    int n;
    vector<int> is;
    vector<vector<int>> js;
    vector<bit> tree;

    void compress(vector<int> &a) {
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    int id(vector<int> &a, int i) {
        return lower_bound(a.begin(), a.end(), i) - a.begin();
    }

    sparse_bit(vector<tuple<char, int, int, int, int>> &q) {
        for (auto [t, i1, j1, i2, j2] : q) {
            if (t == 'U') is.push_back(i1);
            else if (t == 'Q') is.push_back(i1 - 1), is.push_back(i2);
        }
        compress(is);
        n = is.size();

        js.resize(n + 1);
        for (auto [t, i1, j1, i2, j2] : q) {
            if (t == 'U') {
                for (i1 = id(is, i1) + 1; i1 <= n; i1 += bit::lsb(i1)) js[i1].push_back(j1);
            } else if (t == 'Q') {
                for (i1 = id(is, i1 - 1) + 1; i1 > 0; i1 -= bit::lsb(i1)) js[i1].push_back(j1 - 1), js[i1].push_back(j2);
                for (i2 = id(is, i2) + 1; i2 > 0; i2 -= bit::lsb(i2)) js[i2].push_back(j1 - 1), js[i2].push_back(j2);
            }
        }

        tree.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            compress(js[i]);
            tree[i] = bit(js[i].size());
        }
    }

    void update(int i, int j, int x) {
        for (i = id(is, i) + 1; i <= n; i += bit::lsb(i)) tree[i].update(id(js[i], j), x);
    }

    int prefix(int i, int j) {
        int s = 0;
        for (i = id(is, i) + 1; i > 0; i -= bit::lsb(i)) s += tree[i].prefix(id(js[i], j));
        return s;
    }

    int query(int i1, int j1, int i2, int j2) {
        return prefix(i2, j2) - prefix(i1 - 1, j2) - prefix(i2, j1 - 1) + prefix(i1 - 1, j1 - 1);
    }
};
