int hilbert(int x, int y) {
    int h = 0;
    for (int s = 25; s >= 0; --s) {
        int rx = (x >> s) & 1;
        int ry = (y >> s) & 1;
        int qd = (3 * rx) ^ ry;
        h = (h << 2) | qd;
        if (ry == 0) {
            x ^= -rx;
            y ^= -rx;
            swap(x, y);
        }
    }
    return h;
}

vector<int> mo(vector<int> &a, vector<array<int, 4>> &q) {
    for (auto &[h, l, r, id] : q) h = hilbert(l, r);
    sort(q.begin(), q.end());

    int curr = 0;
    auto insert = [&](int x) -> void {};
    auto remove = [&](int x) -> void {};

    vector<int> ans(q.size());
    int i = 0, j = -1;
    for (auto &[h, l, r, id] : q) {
        while (i > l) insert(a[--i]);
        while (j < r) insert(a[++j]);
        while (i < l) remove(a[i++]);
        while (j > r) remove(a[j--]);
        ans[id] = curr;
    }
    return ans;
}
