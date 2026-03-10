int hilbert(int l, int r) {
    static array<int, 4> d = {3, 0, 0, 1};
    int h = 0, c = 0;
    for (int s = 20; s >= 0; --s) {
        int q = (((l >> s & 1) << 1 | (r >> s & 1)) + c) & 3;
        h = h << 2 | q;
        c = (c + d[q]) & 3;
    }
    return h;
}

vector<int> mo(vector<int> &a, vector<array<int, 4>> &q) {
    for (auto &[h, l, r, id] : q) h = hilbert(l, r);
    sort(q.begin(), q.end());

    auto insert = [&](int x) -> void {};
    auto remove = [&](int x) -> void {};

    vector<int> ans(q.size());
    int t = 0, i = 0, j = -1;
    for (auto &[h, l, r, id] : q) {
        while (i > l) insert(a[--i]);
        while (j < r) insert(a[++j]);
        while (i < l) remove(a[i++]);
        while (j > r) remove(a[j--]);
        ans[id] = t;
    }
    return ans;
}
