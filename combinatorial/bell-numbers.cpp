vector<int> bell_numbers(int n) {
    vector<int> b = {1}, row = {1};
    for (int i = 1; i <= n; ++i) {
        vector<int> next = {row.back()};
        for (int x : row) next.push_back((next.back() + x) % mod);
        b.push_back(next[0]);
        row = next;
    }
    return b;
}
