// Sqrt Decomposition: point set, range add and range sum with ceil(n / m) blocks of size m = sqrt(n)
// Time: O(n / m + m) per operation | Space: O(n)
// Note: 0-based | the value at i is arr[i] + lazy[i / m], and sum[b] is the sum of arr in block b
struct sqrt_decomposition {
    int n, m;
    vector<int> arr, sum, lazy;

    int first(int b) {return b * m;}

    int last(int b) {return min(n, b * m + m) - 1;}

    sqrt_decomposition(const vector<int> &arr): n(arr.size()), m(max<int>(1, sqrt(n))), arr(arr) {
        sum.assign((n + m - 1) / m, 0);
        lazy.assign(sum.size(), 0);
        for (int b = 0; b < sum.size(); ++b) pull(b);
    }

    void pull(int b) {
        sum[b] = 0;
        for (int i = first(b); i <= last(b); ++i) sum[b] += arr[i];
    }

    void set(int i, int x) {
        int b = i / m;
        arr[i] = x - lazy[b];
        pull(b);
    }

    void update(int l, int r, int x) {
        int bl = l / m, br = r / m;
        if (bl == br) {
            for (int i = l; i <= r; ++i) arr[i] += x;
            sum[bl] += (r - l + 1) * x;
            return;
        }
        for (int b = bl + 1; b < br; ++b) lazy[b] += x;
        update(l, last(bl), x);
        update(first(br), r, x);
    }

    int query(int l, int r) {
        int bl = l / m, br = r / m, ans = 0;
        if (bl == br) {
            for (int i = l; i <= r; ++i) ans += arr[i];
            return ans + (r - l + 1) * lazy[bl];
        }
        for (int b = bl + 1; b < br; ++b) ans += sum[b] + lazy[b] * m;
        return ans + query(l, last(bl)) + query(first(br), r);
    }
};
