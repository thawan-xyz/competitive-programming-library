struct suffix_array {
    int n;
    str s;
    array<int> suffix, lcp;
    array<int> rank, temp;

    suffix_array(str &base): n(base.length() + 1), s(base + '$'), suffix(n), lcp(n), rank(n), temp(n) {
        for (int i = 0; i < n; ++i) {
            suffix[i] = i;
            rank[i] = s[i];
        }
        for (int k = 1; k < n; k <<= 1) {
            counting_sort(k), counting_sort(0);
            temp[suffix[0]] = 1;
            for (int i = 1; i < n; ++i) {
                int prev = suffix[i - 1];
                int curr = suffix[i];
                if (rank[prev] == rank[curr] and rank[(prev + k) % n] == rank[(curr + k) % n]) {
                    temp[curr] = temp[prev];
                } else {
                    temp[curr] = temp[prev] + 1;
                }
            }
            swap(rank, temp);
            if (rank[suffix[n - 1]] == n) break;
        }
    }

    void counting_sort(int k) {
        int m = max(255, n) + 1;
        array<int> f(m);
        for (int i = 0; i < n; ++i) {
            int r = rank[(suffix[i] + k) % n];
            f[r] += 1;
        }
        for (int i = 1; i < m; ++i) {
            f[i] += f[i - 1];
        }
        for (int i = n - 1; i >= 0; --i) {
            int r = rank[(suffix[i] + k) % n];
            f[r] -= 1;
            temp[f[r]] = suffix[i];
        }
        swap(suffix, temp);
    }

    void longest_common_prefix() {
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
                while (s[i + l] == s[j + l]) l++;
                lcp[p] = l;
                l = max(0, l - 1);
            }
        }
    }

    int compare(int i, str &t) {
        return s.compare(i, t.size(), t);
    }

    int lower_search(str &t) {
        int answer = 0;
        int low = 1, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (compare(suffix[mid], t) < 0) {
                low = mid + 1;
            } else {
                answer = mid;
                high = mid - 1;
            }
        }
        return answer;
    }

    int upper_search(str &t) {
        int answer = n;
        int low = 1, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (compare(suffix[mid], t) <= 0) {
                low = mid + 1;
            } else {
                answer = mid;
                high = mid - 1;
            }
        }
        return answer;
    }

    int search(str &t) {
        int lower = lower_search(t);
        if (compare(suffix[lower], t) != 0) return 0;
        int upper = upper_search(t);
        return upper - lower;
    }
};
