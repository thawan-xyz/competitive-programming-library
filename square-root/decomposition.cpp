struct decomposition {
    int n, m;
    list<int> a, b;

    decomposition(list<int> &base) {
        n = base.size();
        m = max<int>(1, sqrt(n));
        a.resize(n);
        b.resize((n + (m - 1)) / m);
        for (int i = 0; i < n; ++i) {
            a[i] = base[i];
            b[i / m] += a[i];
        }
    }

    void update(int i, int x) {
        a[i] = x;
        int b_i = i / m;
        b[b_i] = 0;
        int l = b_i * m;
        int r = min(n, (b_i + 1) * m) - 1;
        for (int k = l; k <= r; ++k) {
            b[b_i] += a[k];
        }
    }

    int query(int l, int r) {
        int s = 0;
        int b_l = l / m;
        int b_r = r / m;
        if (b_l == b_r) {
            for (int i = l; i <= r; ++i) {
                s += a[i];
            }
        } else {
            for (int i = l; i < (b_l + 1) * m; ++i) {
                s += a[i];
            }
            for (int i = b_l + 1; i < b_r; ++i) {
                s += b[i];
            }
            for (int i = b_r * m; i <= r; ++i) {
                s += a[i];
            }
        }
        return s;
    }
};
