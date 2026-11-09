// Sparse BIT 2D: point update and rectangle sum over a fixed set of points
// Time: Build O(n log n) | Update/Query O(log^2 n) | Space: O(n log n)
struct sparse_bit_2d {
    int n;
    vector<int> rs;
    vector<vector<int>> cs, tree;

    static int lsb(int i) {
        return i & -i;
    }

    int id(const vector<int> &a, int x) {
        return upper_bound(a.begin(), a.end(), x) - a.begin();
    }

    sparse_bit_2d(vector<pair<int, int>> p) {
        for (auto [r, c] : p) rs.push_back(r);
        sort(rs.begin(), rs.end());
        rs.erase(unique(rs.begin(), rs.end()), rs.end());
        n = rs.size();
        cs.resize(n + 1), tree.resize(n + 1);
        sort(p.begin(), p.end(), [](auto &a, auto &b) { return a.second < b.second; });
        for (auto [r, c] : p) {
            for (int i = id(rs, r); i <= n; i += lsb(i)) {
                if (cs[i].empty() or cs[i].back() != c) cs[i].push_back(c);
            }
        }
        for (int i = 1; i <= n; ++i) tree[i].resize(cs[i].size() + 1);
    }

    void update(int r, int c, int v) {
        for (int i = id(rs, r); i <= n; i += lsb(i)) {
            for (int j = id(cs[i], c); j < tree[i].size(); j += lsb(j)) tree[i][j] += v;
        }
    }

    int prefix(int r, int c) {
        int s = 0;
        for (int i = id(rs, r); i > 0; i -= lsb(i)) {
            for (int j = id(cs[i], c); j > 0; j -= lsb(j)) s += tree[i][j];
        }
        return s;
    }

    int query(int r1, int c1, int r2, int c2) {
        return prefix(r2, c2) - prefix(r1 - 1, c2) - prefix(r2, c1 - 1) + prefix(r1 - 1, c1 - 1);
    }
};
