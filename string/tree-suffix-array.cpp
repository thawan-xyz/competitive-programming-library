// Tree Suffix Array: lexicographical sorting of all tree paths (node to root)
// Time: build O(N log^2 N) | LCP O(log N) | search O(|P| log N) | Space: O(N log N)
// Note: 1-indexed nodes, node 0 is reserved as a sentinel root with s[0] = '$'
struct tree_suffix_array {
    int n, m, log;
    string s;
    vector<int> suf, lcp, temp, depth;
    vector<vector<int>> &g, up, rank;

    void dfs(int a, int p, int d) {
        up[a][0] = p;
        depth[a] = d;
        for (int k = 1; k <= log; ++k) {
            up[a][k] = up[up[a][k - 1]][k - 1];
        }
        for (int b : g[a]) if (b != p) {
            dfs(b, a, d + 1);
        }
    }

    int jump(int a, int k) {
        for (int i = 0; k > 0; ++i, k >>= 1) {
            if (k & 1) a = up[a][i];
        }
        return a;
    }

    void sort(int k, int j) {
        vector<int> f(m + 1);
        for (int i = 0; i < n; ++i) {
            int r = rank[k][jump(suf[i], j)];
            f[r]++;
        }
        for (int i = 1; i <= m; ++i) {
            f[i] += f[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            int r = rank[k][jump(suf[i], j)];
            f[r]--;
            temp[f[r]] = suf[i];
        }
        swap(suf, temp);
    }

    tree_suffix_array(const string &letters, vector<vector<int>> &graph): n(letters.length()), m(0), log(__lg(n | 1) + 1),
    s(letters), suf(n), lcp(n), temp(n), depth(n), g(graph), up(n, vector<int>(log + 1)), rank(log + 1, vector<int>(n)) {
        dfs(1, 0, 1);
        for (int i = 1; i < n; ++i) {
            suf[i] = i;
            rank[0][i] = s[i];
            m = max<int>(m, s[i]);
        }
        for (int k = 0; k < log; ++k) {
            int len = 1 << k;
            sort(k, len);
            sort(k, 0);
            rank[k + 1][suf[0]] = 0;
            int val = 0;
            for (int i = 1; i < n; ++i) {
                int prev = suf[i - 1];
                int curr = suf[i];
                int j_prev = jump(prev, len);
                int j_curr = jump(curr, len);
                if (rank[k][prev] == rank[k][curr] and rank[k][j_prev] == rank[k][j_curr]) {
                    rank[k + 1][curr] = val;
                } else {
                    rank[k + 1][curr] = ++val;
                }
            }
            m = val;
            if (m == n - 1) {
                for (int h = k + 1; h <= log; ++h) {
                    for (int i = 0; i < n; ++i) {
                        rank[h][i] = rank[k + 1][i];
                    }
                }
                break;
            }
        }
    }

    int longest_common_prefix(int a, int b) {
        if (a == b) return depth[a];
        int answer = 0;
        for (int k = log; k >= 0 and a != 0 and b != 0; --k) if (rank[k][a] == rank[k][b]) {
            int len = 1 << k;
            answer += len;
            a = jump(a, len);
            b = jump(b, len);
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
            a = up[a][0];
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
