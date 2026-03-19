vector<int> mtt(vector<int> &a, vector<int> &b, int mod) {
    vector<int> mods = {998244353, 1004535809, 469762049};

    vector<int> c1 = convolution(a, b, 3, mods[0]);
    vector<int> c2 = convolution(a, b, 3, mods[1]);
    vector<int> c3 = convolution(a, b, 3, mods[2]);

    int n = c1.size();
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        vector<int> rems = {c1[i], c2[i], c3[i]};
        int128 x = chinese_remainder_theorem(rems, mods);
        c[i] = x % mod;
    }
    return c;
}
