list<int> or_convolution(list<int> &a, list<int> &b) {
    int s = max(a.size(), b.size());
    int m = (s == 1) ? 1 : 1 << (32 - __builtin_clz(s - 1));
    int n = __builtin_ctz(m);

    a.resize(m), b.resize(m);
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < m; ++mask) {
            if (mask & (1 << i)) {
                a[mask] += a[mask ^ (1 << i)];
                b[mask] += b[mask ^ (1 << i)];
            }
        }
    }

    list<int> c(m);
    for (int mask = 0; mask < m; ++mask) {
        c[mask] = a[mask] * b[mask];
    }

    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < m; ++mask) {
            if (mask & (1 << i)) {
                c[mask] -= c[mask ^ (1 << i)];
            }
        }
    }
    return c;
}

list<int> and_convolution(list<int> &a, list<int> &b) {
    int s = max(a.size(), b.size());
    int m = (s == 1) ? 1 : 1 << (32 - __builtin_clz(s - 1));
    int n = __builtin_ctz(m);

    a.resize(m), b.resize(m);
    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < m; ++mask) {
            if (not (mask & (1 << i))) {
                a[mask] += a[mask ^ (1 << i)];
                b[mask] += b[mask ^ (1 << i)];
            }
        }
    }

    list<int> c(m);
    for (int mask = 0; mask < m; ++mask) {
        c[mask] = a[mask] * b[mask];
    }

    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < m; ++mask) {
            if (not (mask & (1 << i))) {
                c[mask] -= c[mask ^ (1 << i)];
            }
        }
    }
    return c;
}
