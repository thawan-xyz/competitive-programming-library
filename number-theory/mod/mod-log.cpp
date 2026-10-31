int mod_log(int a, int b, int mod) {
    a %= mod, b %= mod;
    int k = 1, steps = 0;
    for (int g = gcd(a, mod); g > 1; g = gcd(a, mod)) {
        if (b == k) return steps;
        if (b % g != 0) return -1;
        b /= g, mod /= g, steps++;
        k = k * (a / g) % mod;
    }
    int n = sqrt(mod) + 1, giant = 1;
    for (int i = 0; i < n; ++i) giant = giant * a % mod;
    vector<array<int, 2>> baby;
    for (int q = 0, cur = b; q <= n; ++q) {
        baby.push_back({cur, -q});
        cur = cur * a % mod;
    }
    sort(baby.begin(), baby.end());
    for (int p = 1, cur = k; p <= n; ++p) {
        cur = cur * giant % mod;
        auto itr = lower_bound(baby.begin(), baby.end(), array<int, 2>{cur, -n});
        if (itr != baby.end() and (*itr)[0] == cur) return n * p + (*itr)[1] + steps;
    }
    return -1;
}
