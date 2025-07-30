struct suffix_array {
    int n;
    str &s;
    array<int> suffix, lcp;
    array<int> rank, temp;

    suffix_array(str &s): n(s.length()), s(s), suffix(n), lcp(n), rank(n), temp(n) {
        for (int i = 0; i < n; ++i) {
            suffix[i] = i;
            rank[i] = s[i] + 1;
        }
        for (int k = 1; k < n; k <<= 1) {
            counting_sort(k), counting_sort(0);
            temp[suffix[0]] = 1;
            for (int i = 1; i < n; ++i) {
                int prev = suffix[i - 1];
                int curr = suffix[i];
                temp[curr] = temp[prev];
                bool same = rank[prev] == rank[curr] and ((curr + k < n ? rank[curr + k] : 0) == (prev + k < n ? rank[prev + k] : 0));
                if (not same) temp[curr] += 1;
            }
            swap(rank, temp);
            if (rank[suffix[n - 1]] == n) break;
        }
    }

    void counting_sort(int k) {
        int m = max(256, n) + 1;
        array<int> f(m);
        for (int i = 0; i < n; ++i) {
            int r = suffix[i] + k < n ? rank[suffix[i] + k] : 0;
            f[r] += 1;
        }
        for (int i = 1; i < m; ++i) {
            f[i] += f[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            int r = suffix[i] + k < n ? rank[suffix[i] + k] : 0;
            f[r] -= 1;
            temp[f[r]] = suffix[i];
        }
        swap(suffix, temp);
    }

    void compute_lcp() {
        array<int> inverse(n);
        for (int i = 0; i < n; ++i) {
            inverse[suffix[i]] = i;
        }
        int l = 0;
        for (int i = 0; i < n; ++i) {
            int p = inverse[i];
            if (p == 0) {
                lcp[p] = 0;
                l = 0;
            } else {
                int j = suffix[p - 1];
                while ((i + l < n and j + l < n) and s[i + l] == s[j + l]) l++;
                lcp[p] = l;
                l = max(0, l - 1);
            }
        }
    }
};
