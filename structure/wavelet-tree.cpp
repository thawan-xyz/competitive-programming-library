struct wavelet_tree {
    int size, sigma;
    list<int> low, high;
    list<list<int>> prefix;

    wavelet_tree(list<int> &base, int sigma): size(base.size()), sigma(sigma), low(4 * size), high(4 * size), prefix(4 * size) {
        build(base, 0, 0, sigma);
    }

    void build(list<int> &base, int node, int i, int j) {
        low[node] = i, high[node] = j;
        prefix[node].resize(base.size());

        if (low[node] == high[node]) {
            for (int k = 0; k < base.size(); ++k) {
                prefix[node][k] = k + 1;
            }
        } else {
            list<int> left; left.reserve(base.size());
            list<int> right; right.reserve(base.size());

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

            if (not left.empty()) build(left, (2 * node) + 1, low[node], mid);
            if (not right.empty()) build(right, (2 * node) + 2, mid + 1, high[node]);
        }
    }

    int query(int value, int left, int right, int node = 0) {
        if (left > right or value < low[node]) return 0;
        if (value >= high[node]) return (right - left) + 1;

        int i = (left == 0) ? 0 : prefix[node][left - 1], j = prefix[node][right];
        return query(value, i, j - 1, (2 * node) + 1) + query(value, left - i, right - j, (2 * node) + 2);
    }

    int kth(int k, int left, int right, int node = 0) {
        if (low[node] == high[node]) return low[node];

        int i = (left == 0) ? 0 : prefix[node][left - 1], j = prefix[node][right];
        if (k <= j - i) {
            return kth(k, i, j - 1, (2 * node) + 1);
        } else {
            return kth(k - (j - i), left - i, right - j, (2 * node) + 2);
        }
    }
};
