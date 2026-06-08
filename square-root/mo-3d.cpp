vector<int> mo_3d(vector<int> &a, vector<array<int, 4>> &q, vector<array<int, 2>> &u, float m = 1.0) {
    int b = clamp<int>(pow(a.size(), 2.0 / 3.0) * m, 1, a.size());
    sort(q.begin(), q.end(), [&](const array<int, 4> &x, const array<int, 4> &y) {
        int bl_x = x[0] / b, bl_y = y[0] / b;
        if (bl_x != bl_y) return bl_x < bl_y;
        int br_x = x[1] / b, br_y = y[1] / b;
        if (br_x != br_y) return (bl_x & 1) ? (br_x < br_y) : (br_x > br_y);
        return (br_x & 1) ? (x[2] < y[2]) : (x[2] > y[2]);
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
