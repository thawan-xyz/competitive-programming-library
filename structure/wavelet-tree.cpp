struct wavelet_tree {
    int size;
    array<int> low, high;
    array<array<int>> prefix;

    wavelet_tree(array<int> &base): size(base.size()), low(4 * size), high(4 * size), prefix(4 * size) {
        int left = 0, right = 0;
        for (int k = 0; k < base.size(); ++k) {
            left = min(left, base[k]);
            right = max(right, base[k]);
        }
        build(base, left, right);
    }

    void build(array<int> &base, int i, int j, int node = 1) {
        low[node] = i, high[node] = j;
        prefix[node].resize(base.size());

        if (low[node] == high[node]) {
            for (int k = 0; k < base.size(); ++k) {
                prefix[node][k] = k + 1;
            }
        } else {
            array<int> left; left.reserve(base.size());
            array<int> right; right.reserve(base.size());

            int mid = (low[node] + high[node]) / 2;
            for (int k = 0; k < base.size(); ++k) {
                prefix[node][k] = (k == 0) ? 0 : prefix[node][k - 1];
                if (base[k] <= mid) {
                    prefix[node][k]++;
                    left.push_back(base[k]);
                } else {
                    right.push_back(base[k]);
                }
            }

            if (not left.empty()) build(left, low[node], mid, node << 1);
            if (not right.empty()) build(right, mid + 1, high[node], (node << 1) | 1);
        }
    }

    int query(int value, int left, int right, int node = 1) {
        if (left > right or value < low[node]) return 0;
        if (value >= high[node]) return (right - left) + 1;

        int i = (left == 0) ? 0 : prefix[node][left - 1], j = prefix[node][right];
        return query(value, i, j - 1, node << 1) + query(value, left - i, right - j, (node << 1) | 1);
    }

    int kth(int k, int left, int right, int node = 1) {
        if (low[node] == high[node]) return low[node];

        int i = (left == 0) ? 0 : prefix[node][left - 1], j = prefix[node][right];
        if (k <= j - i) {
            return kth(k, i, j - 1, node << 1);
        } else {
            return kth(k - (j - i), left - i, right - j, (node << 1) | 1);
        }
    }
};
