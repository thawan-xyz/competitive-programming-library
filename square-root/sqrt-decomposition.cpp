// Sqrt Decomposition: point set, range add and range sum with blocks of size m = f * sqrt(n)
// Time: O(n / m + m) per operation | Space: O(n)
// Note: 0-based | the value at i is arr[i] + lazy[i / m]
struct sqrt_decomposition {
    int n, m;
    vector<int> arr, sum, lazy;

    void build(int b) {
        sum[b] = 0;
        for (int i = first(b); i <= last(b); ++i) {
            sum[b] += arr[i];
        }
    }

    sqrt_decomposition(const vector<int> &arr, float f = 1): n(arr.size()), arr(arr) {
        m = max<int>(1, f * sqrt(n));
        sum.assign(n / m + 1, 0);
        lazy.assign(n / m + 1, 0);
        for (int b = 0; b <= n / m; ++b) build(b);
    }

    int first(int b) {
        return b * m;
    }

    int last(int b) {
        return min(n, b * m + m) - 1;
    }

    void set(int i, int x) {
        int b = i / m;
        arr[i] = x - lazy[b];
        build(b);
    }

    void update(int l, int r, int x) {
        int bl = l / m, br = r / m;
        if (bl >= br) {
            for (int i = l; i <= r; ++i) arr[i] += x;
            build(bl);
            return;
        }
        for (int b = bl + 1; b < br; ++b) lazy[b] += x;
        update(l, last(bl), x);
        update(first(br), r, x);
    }

    int query(int l, int r) {
        int bl = l / m, br = r / m, s = 0;
        if (bl >= br) {
            for (int i = l; i <= r; ++i) s += arr[i] + lazy[bl];
            return s;
        }
        for (int b = bl + 1; b < br; ++b) s += sum[b] + lazy[b] * m;
        return s + query(l, last(bl)) + query(first(br), r);
    }
};
