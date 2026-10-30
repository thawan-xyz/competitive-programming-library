// Suffix Array: sorts all suffixes of s, with pattern search and k-th smallest substring (counting repeats or not)
// Time: build O(N log N) | search O(M log N) | kth O(N log N) | kth_distinct O(N) | Space: O(N)
// Note: suf = sorted suffix starts | rank = position of the suffix i in suf | search = [l, r) | kth = (start, len)
struct suffix_array {
    int n;
    string s;
    vector<int> suf, rank, lcp;

    suffix_array(const string &s): n(s.size()), s(s), suf(n + 1), rank(n + 1) {
        vector<int> temp(n + 1), cnt(max<int>(256, n + 1));
        auto sort = [&]() {
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i <= n; ++i) cnt[rank[i]]++;
            for (int i = 1; i < cnt.size(); ++i) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 0; --i) temp[--cnt[rank[suf[i]]]] = suf[i];
            swap(suf, temp);
        };
        for (int i = 0; i < n; ++i) rank[i] = s[i];
        iota(suf.begin(), suf.end(), 0);
        sort();
        for (int k = 1; true; k *= 2) {
            for (int &i : suf) i = (i >= k) ? i - k : i - k + n + 1;
            sort();
            temp[suf[0]] = 0;
            for (int i = 1; i <= n; ++i) {
                int a = suf[i - 1], b = suf[i];
                temp[b] = temp[a] + (rank[a] != rank[b] or rank[a + k] != rank[b + k]);
            }
            swap(rank, temp);
            if (rank[suf[n]] == n) break;
        }
        suf.erase(suf.begin()), rank.pop_back();
        for (int i = 0; i < n; ++i) rank[suf[i]] = i;
    }

    void longest_common_prefix() {
        lcp.assign(n, 0);
        for (int i = 0, h = 0; i < n; ++i) if (rank[i] > 0) {
            int j = suf[rank[i] - 1];
            while (i + h < n and j + h < n and s[i + h] == s[j + h]) h++;
            lcp[rank[i]] = h;
            if (h > 0) h--;
        }
    }

    array<int, 2> search(const string &t) {
        auto cmp = [&](int i) {return s.compare(i, t.size(), t);};
        int l = partition_point(suf.begin(), suf.end(), [&](int i) {return cmp(i) < 0;}) - suf.begin();
        int r = partition_point(suf.begin() + l, suf.end(), [&](int i) {return cmp(i) == 0;}) - suf.begin();
        return {l, r};
    }

    array<int, 2> kth_distinct(int k) {
        for (int i = 0; i < n; ++i) {
            int cnt = n - suf[i] - lcp[i];
            if (k < cnt) return {suf[i], lcp[i] + k + 1};
            k -= cnt;
        }
        return {-1, -1};
    }

    array<int, 2> kth(int k) {
        vector<int> pre(n + 1);
        for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + n - suf[i];
        if (k >= pre[n]) return {-1, -1};
        int l = 0, r = n, len = 0;
        while (true) {
            if (n - suf[l] == len) l++;
            char c = s[suf[l] + len];
            int m = partition_point(suf.begin() + l, suf.begin() + r, [&](int i) {return s[i + len] <= c;}) - suf.begin();
            int cnt = pre[m] - pre[l] - (m - l) * len;
            if (k >= cnt) {
                k -= cnt, l = m;
            } else {
                r = m, len++;
                if (k < r - l) return {suf[l], len};
                k -= r - l;
            }
        }
        return {-1, -1};
    }
};
