struct hasher {
    int n;
    int a = 41, b = 53;
    int m1 = 1e9 + 7, m2 = 1e9 + 9;
    array<int> p1, p2;
    array<int> h1, h2;
    array<int> r1, r2;

    hasher(str &s): n(s.length()), p1(n + 1), p2(n + 1), h1(n), h2(n), r1(n), r2(n) {
        p1[0] = 1;
        p2[0] = 1;
        for (int i = 1; i <= n; ++i) {
            p1[i] = (a * p1[i - 1]) % m1;
            p2[i] = (b * p2[i - 1]) % m2;
        }

        h1[0] = s[0];
        h2[0] = s[0];
        for (int i = 1; i < n; ++i) {
            h1[i] = (a * h1[i - 1] + s[i]) % m1;
            h2[i] = (b * h2[i - 1] + s[i]) % m2;
        }

        r1[n - 1] = s[n - 1];
        r2[n - 1] = s[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            r1[i] = (a * r1[i + 1] + s[i]) % m1;
            r2[i] = (b * r2[i + 1] + s[i]) % m2;
        }
    }

    int hash(int l, int r) {
        int x = h1[r];
        if (l > 0) x = (h1[r] - h1[l - 1] * p1[r - l + 1]) % m1;
        if (x < 0) x += m1;

        int y = h2[r];
        if (l > 0) y = (h2[r] - h2[l - 1] * p2[r - l + 1]) % m2;
        if (y < 0) y += m2;

        return (x << 32) | y;
    }

    int reverse(int l, int r) {
        int x = r1[l];
        if (r + 1 < n) x = (r1[l] - r1[r + 1] * p1[r - l + 1]) % m1;
        if (x < 0) x += m1;

        int y = r2[l];
        if (r + 1 < n) y = (r2[l] - r2[r + 1] * p2[r - l + 1]) % m2;
        if (y < 0) y += m2;

        return (x << 32) | y;
    }
};
