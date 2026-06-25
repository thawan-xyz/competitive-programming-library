// Tree Suffix Array: lexicographical sorting of all tree paths (node to root)
// Time: build O(N log N) | LCP O(log N) | search O(|P| log N) | Space: O(N log N)
// Note: 1-indexed nodes, node 0 is reserved as a sentinel root with s[0] = '$'
struct tree_suffix_array {
    int n, m, log;
    string s;
    vector<int> suf, lcp, temp, depth;
    vector<vector<int>> up, rank;

    void dfs(int a, int p, int d, vector<vector<int>> &g) {
        up[0][a] = p;
        depth[a] = d;
        for (int k = 1; k <= log; ++k) {
            up[k][a] = up[k - 1][up[k - 1][a]];
        }
        for (int b : g[a]) if (b != p) {
            dfs(b, a, d + 1, g);
        }
    }

    void sort(int k, bool jump) {
        vector<int> f(m + 1);
        for (int i = 0; i < n; ++i) {
            int h = suf[i];
            if (jump) h = up[k][h];
            int r = rank[k][h];
            f[r]++;
        }
        for (int i = 1; i <= m; ++i) {
            f[i] += f[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            int h = suf[i];
            if (jump) h = up[k][h];
            int r = rank[k][h];
            f[r]--;
            temp[f[r]] = suf[i];
        }
        swap(suf, temp);
    }

    tree_suffix_array(const string &letters, vector<vector<int>> &g): n(letters.length()), m(0), log(__lg(n | 1) + 1),
    s(letters), suf(n), lcp(n), temp(n), depth(n), up(log + 1, vector<int>(n)), rank(log + 1, vector<int>(n)) {
        dfs(1, 0, 1, g);
        for (int i = 0; i < n; ++i) {
            suf[i] = i;
            rank[0][i] = s[i];
            m = max<int>(m, s[i]);
        }
        for (int k = 0; k < log; ++k) {
            sort(k, true);
            sort(k, false);
            rank[k + 1][suf[0]] = 0;
            int val = 0;
            for (int i = 1; i < n; ++i) {
                int prev = suf[i - 1];
                int curr = suf[i];
                int j_prev = up[k][prev];
                int j_curr = up[k][curr];
                if (rank[k][prev] == rank[k][curr] and rank[k][j_prev] == rank[k][j_curr]) {
                    rank[k + 1][curr] = val;
                } else {
                    rank[k + 1][curr] = ++val;
                }
            }
            m = val;
            if (m == n - 1) {
                for (int h = k + 1; h <= log; ++h) rank[h] = rank[k + 1];
                break;
            }
        }
    }

    int longest_common_prefix(int a, int b) {
        if (a == b) return depth[a];
        int answer = 0;
        for (int k = log; k >= 0 and a != 0 and b != 0; --k) if (rank[k][a] == rank[k][b]) {
            answer += 1 << k;
            a = up[k][a];
            b = up[k][b];
        }
        return answer;
    }

    void build_longest_common_prefix() {
        for (int i = 1; i < n; ++i) {
            lcp[i] = longest_common_prefix(suf[i], suf[i - 1]);
        }
    }

    int compare(int a, string &t) {
        for (int i = 0; i < t.length(); ++i) {
            if (a == 0) return -1;
            if (s[a] != t[i]) return s[a] < t[i] ? -1 : +1;
            a = up[0][a];
        }
        return 0;
    }

    int lower_search(string &t) {
        int answer = 0;
        int low = 1, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (compare(suf[mid], t) < 0) {
                low = mid + 1;
            } else {
                answer = mid;
                high = mid - 1;
            }
        }
        return answer;
    }

    int upper_search(string &t) {
        int answer = n;
        int low = 1, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (compare(suf[mid], t) <= 0) {
                low = mid + 1;
            } else {
                answer = mid;
                high = mid - 1;
            }
        }
        return answer;
    }

    int search(string &t) {
        int lower = lower_search(t);
        if (compare(suf[lower], t) != 0) return 0;
        int upper = upper_search(t);
        return upper - lower;
    }

    pair<int, int> range(string &t) {
        int lower = lower_search(t);
        if (compare(suf[lower], t) != 0) return {-1, -1};
        int upper = upper_search(t);
        return {lower, upper - 1};
    }
};
