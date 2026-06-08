// Mo's Algorithm 3D: offline range queries with point updates
// Time: O(N^(5/3)) | Space: O(N + Q + U)
// Q elements: {l, r, t, id} | t = # of updates prior to query | id = original query index
// U elements: {i, x} | i = array index to update | x = new value
// M parameter: block size multiplier to tune the N^(2/3) block size
// Note: implement 'insert', 'remove', and 'curr' state according to your specific problem
vector<int> mo_3d(vector<int> &a, vector<array<int, 4>> &q, vector<array<int, 2>> &u, float m = 1.0) {
    int b = clamp<int>(m * pow(a.size(), 2.0 / 3.0), 1, a.size());
    auto block = [&](int i) -> int {
        return i / b;
    };

    sort(q.begin(), q.end(), [&](const array<int, 4> &x, const array<int, 4> &y) {
        if (block(x[0]) != block(y[0])) return block(x[0]) < block(y[0]);
        if (block(x[1]) != block(y[1])) return (block(x[0]) & 1) ? block(x[1]) < block(y[1]) : block(x[1]) > block(y[1]);
        return (block(x[1]) & 1) ? x[2] < y[2] : x[2] > y[2];
    });

    int curr = 0;
    auto insert = [&](int x) -> void {};
    auto remove = [&](int x) -> void {};

    auto update = [&](int t, int l, int r) -> void {
        int i = u[t][0];
        if (l <= i and i <= r) {
            remove(a[i]);
            swap(a[i], u[t][1]);
            insert(a[i]);
        } else {
            swap(a[i], u[t][1]);
        }
    };

    vector<int> ans(q.size());
    int h = 0, i = 0, j = -1;
    for (auto &[l, r, t, id] : q) {
        while (h < t) update(h++, i, j);
        while (h > t) update(--h, i, j);
        while (i > l) insert(a[--i]);
        while (j < r) insert(a[++j]);
        while (i < l) remove(a[i++]);
        while (j > r) remove(a[j--]);
        ans[id] = curr;
    }
    return ans;
}
