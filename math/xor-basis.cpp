struct xor_basis {
    static constexpr int log = 30;
    int n = 0, size = 0;
    array<int, log> basis = {};

    void insert(int x) {
        n += 1;
        for (int i = log - 1; i >= 0; --i) if ((x >> i) & 1) {
            if (basis[i] == 0) {
                basis[i] = x;
                size += 1;
                return;
            } else {
                x ^= basis[i];
            }
        }
    }

    int max() {
        int x = 0;
        for (int i = log - 1; i >= 0; --i) if (((x >> i) & 1) == 0) {
            x ^= basis[i];
        }
        return x;
    }

    void build() {
        for (int i = log - 1; i >= 0; --i) if (basis[i] != 0) {
            for (int j = i - 1; j >= 0; --j) if (((basis[i] >> j) & 1) and basis[j] != 0) {
                basis[i] ^= basis[j];
            }
        }
    }

    int kth(int k) {
        if ((k >> size) != 0) return -1;
        int x = 0;
        for (int i = 0; i < log; ++i) if (basis[i] != 0) {
            if (k & 1) x ^= basis[i];
            k >>= 1;
        }
        return x;
    }

    int operator[](int k) {
        if (n - size > 60) return 0;
        return kth(k >> (n - size));
    }
};
