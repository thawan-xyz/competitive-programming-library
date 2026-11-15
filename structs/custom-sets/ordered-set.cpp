#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T, int B = 256>
struct ordered_set {
    int n = 0;
    vector<int> bit;
    vector<vector<T>> block;

    int size() {
        return n;
    }

    void update(int i, int x) {
        for (i += 1; i < bit.size(); i += i & -i) bit[i] += x;
    }

    void build() {
        bit.assign(block.size() + 1, 0);
        for (int i = 0; i < block.size(); ++i) update(i, block[i].size());
    }

    pair<int, int> find(const T &x) {
        if (block.empty()) block.assign(1, {}), bit.assign(2, 0);
        int i = partition_point(block.begin(), block.end() - 1, [&](auto &b) { return b.back() < x; }) - block.begin();
        return {i, lower_bound(block[i].begin(), block[i].end(), x) - block[i].begin()};
    }

    void insert(const T &x) {
        auto [i, j] = find(x);
        block[i].insert(block[i].begin() + j, x), n++;
        if (block[i].size() < 2 * B) return update(i, 1);
        block.insert(block.begin() + i + 1, vector<T>(block[i].begin() + B, block[i].end()));
        block[i].resize(B), build();
    }

    bool remove(const T &x) {
        auto [i, j] = find(x);
        if (j == block[i].size() or x < block[i][j]) return false;
        block[i].erase(block[i].begin() + j), n--;
        if (block[i].empty() and block.size() > 1) block.erase(block.begin() + i), build();
        else update(i, -1);
        return true;
    }

    int less(const T &x) {
        auto [i, j] = find(x);
        while (i > 0) j += bit[i], i -= i & -i;
        return j;
    }

    T kth(int k) {
        int i = 0;
        for (int s = 1 << __lg(bit.size()); s > 0; s /= 2) {
            if (i + s < bit.size() and bit[i + s] <= k) i += s, k -= bit[i];
        }
        return block[i][k];
    }
};
