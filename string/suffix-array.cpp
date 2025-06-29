struct suffix_array {
    int n;
    str s;
    array<int> suf, lcp;

    suffix_array(str &t): n(t.length()), s(t), suf(n), lcp(n) {
        array<int> rank(n), temp(n);
        function<void(int)> csort = [&](int k) -> void {
            int m = max(256, n) + 1;
            array<int> f(m);
            for (int i = 0; i < n; ++i) {
                int r = suf[i] + k < n ? rank[suf[i] + k] : 0;
                f[r] += 1;
            }
            for (int i = 1; i < m; ++i) {
                f[i] += f[i - 1];
            }
            for (int i = n - 1; i >= 0; --i) {
                int r = suf[i] + k < n ? rank[suf[i] + k] : 0;
                f[r] -= 1;
                temp[f[r]] = suf[i];
            }
            swap(suf, temp);
        };

        for (int i = 0; i < n; ++i) {
            suf[i] = i;
            rank[i] = s[i] + 1;
        }
        for (int k = 1; k < n; k <<= 1) {
            csort(k), csort(0);
            temp[suf[0]] = 1;
            for (int i = 1; i < n; ++i) {
                int prev = suf[i - 1];
                int curr = suf[i];
                temp[curr] = temp[prev];
                bool same = rank[prev] == rank[curr] and ((curr + k < n ? rank[curr + k] : 0) == (prev + k < n ? rank[prev + k] : 0));
                if (not same) temp[curr] += 1;
            }
            swap(rank, temp);
            if (rank[suf[n - 1]] == n) break;
        }

        array<int> inv(n);
        for (int i = 0; i < n; ++i) {
            inv[suf[i]] = i;
        }
        int h = 0;
        for (int i = 0; i < n; ++i) {
            int p = inv[i];
            if (p == 0) {
                lcp[p] = 0;
            } else {
                int j = suf[p - 1];
                while ((i + h < n and j + h < n) and s[i + h] == s[j + h]) h++;
                lcp[p] = h;
                if (h > 0) h--;
            }
        }
    }
};
