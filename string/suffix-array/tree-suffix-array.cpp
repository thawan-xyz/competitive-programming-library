// Tree Suffix Array: sorts the nodes by their string, the letters s[v] from v up to the root, with pattern search and lcp of any two
// Time: build O(N log N) | search O(M log N) | longest_common_prefix(a, b) O(log N) | less_equal O(log N) | Space: O(N log N)
// Note: root = 0 | suf = sorted nodes | rank[log][v] = number of distinct strings smaller than the string of v | search = [l, r)
struct tree_suffix_array {
    int n, log;
    string s;
    vector<int> suf, depth, lcp;
    vector<vector<int>> up, rank;

    tree_suffix_array(const string &s, const vector<vector<int>> &g): n(s.size()), s(s), suf(n + 1), depth(n + 1), lcp(n) {
        vector<int> p(n + 1, n), q = {0};
        depth[0] = 1;
        for (int i = 0; i < q.size(); ++i) {
            int a = q[i];
            for (int b : g[a]) if (b != p[a]) {
                p[b] = a, depth[b] = depth[a] + 1;
                q.push_back(b);
            }
        }
        vector<int> temp(n + 1), cnt(max<int>(256, n + 1));
        auto sort = [&](const vector<int> &key) {
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i <= n; ++i) cnt[key[i]]++;
            for (int i = 1; i < cnt.size(); ++i) cnt[i] += cnt[i - 1];
            for (int i = n; i >= 0; --i) temp[--cnt[key[suf[i]]]] = suf[i];
            swap(suf, temp);
        };
        up = {p};
        rank = {vector<int>(n + 1)};
        for (int i = 0; i < n; ++i) rank[0][i] = s[i];
        iota(suf.begin(), suf.end(), 0);
        for (int k = 0; true; ++k) {
            vector<int> key(n + 1), nxt(n + 1), jump(n + 1);
            for (int i = 0; i <= n; ++i) key[i] = rank[k][up[k][i]];
            sort(key);
            sort(rank[k]);
            for (int i = 1; i <= n; ++i) {
                int a = suf[i - 1], b = suf[i];
                nxt[b] = nxt[a] + (rank[k][a] != rank[k][b] or key[a] != key[b]);
            }
            rank.push_back(nxt);
            if (k > 0 and nxt[suf[n]] == rank[k][suf[n]]) break;
            for (int i = 0; i <= n; ++i) jump[i] = up[k][up[k][i]];
            up.push_back(jump);
        }
        log = up.size();
        suf.erase(suf.begin());
        for (int i = 1; i < n; ++i) lcp[i] = longest_common_prefix(suf[i - 1], suf[i]);
    }

    int longest_common_prefix(int a, int b) {
        if (rank[log][a] == rank[log][b]) return depth[a];
        int h = 0;
        for (int k = log - 1; k >= 0; --k) if (rank[k][a] == rank[k][b]) {
            h += 1 << k;
            a = up[k][a], b = up[k][b];
        }
        return h;
    }

    array<int, 2> search(const string &t) {
        auto cmp = [&](int i) {
            for (char c : t) {
                if (i == n or s[i] < c) return -1;
                if (s[i] > c) return 1;
                i = up[0][i];
            }
            return 0;
        };
        int l = partition_point(suf.begin(), suf.end(), [&](int i) {return cmp(i) < 0;}) - suf.begin();
        int r = partition_point(suf.begin() + l, suf.end(), [&](int i) {return cmp(i) == 0;}) - suf.begin();
        return {l, r};
    }

    int less_equal(const string &t) {
        auto cmp = [&](int i) {
            for (char c : t) {
                if (i == n or s[i] < c) return true;
                if (s[i] > c) return false;
                i = up[0][i];
            }
            return i == n;
        };
        return partition_point(suf.begin(), suf.end(), cmp) - suf.begin();
    }
};
