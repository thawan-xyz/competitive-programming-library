// XOR Basis: linear basis for subset XOR representation and query operations
// Time: insert/contains/max/kth O(log) | Space: O(log) where log is the maximum bit length (30)
// Note: kth(k) returns k-th smallest distinct XOR | operator[k] returns k-th smallest among all 2^n subsets (with duplicates)
struct xor_basis {
    static constexpr int log = 30;
    int n = 0, r = 0;
    array<int, log> basis = {};

    void insert(int x) {
        for (int i = log - 1; i >= 0; --i) if ((x >> i) & 1) {
            if (basis[i] == 0) {
                for (int j = i - 1; j >= 0; --j) if ((x >> j) & 1) {
                    x ^= basis[j];
                }
                basis[i] = x;
                r += 1;
                for (int j = log - 1; j > i; --j) if ((basis[j] >> i) & 1) {
                    basis[j] ^= x;
                }
                break;
            } else {
                x ^= basis[i];
            }
        }
        n += 1;
    }

    bool contains(int x) {
        for (int i = log - 1; i >= 0; --i) if ((x >> i) & 1) {
            x ^= basis[i];
        }
        return x == 0;
    }

    int max() {
        int x = 0;
        for (int i = log - 1; i >= 0; --i) if (((x >> i) & 1) == 0) {
            x ^= basis[i];
        }
        return x;
    }

    int kth(int k) {
        if ((k >> r) != 0) return -1;
        int x = 0;
        for (int i = 0; i < log; ++i) if (basis[i] != 0) {
            if (k & 1) x ^= basis[i];
            k >>= 1;
        }
        return x;
    }

    int operator[](int k) {
        if (n - r > 60) return 0;
        return kth(k >> (n - r));
    }

    int ways(int x) {
        if (not contains(x)) return 0;
        return mod_pow(2, n - r);
    }
};
