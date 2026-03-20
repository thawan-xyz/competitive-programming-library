// Range Set: Bitset optimized for Range Updates and Queries
// Time: O(N/64) per operation | Space: O(N/64)
// Note: uint = uint64_t (unsigned long long)
struct range_set {
    int n;
    vector<uint> data;

    range_set(int n): n(n), data((n + 63) / 64) {}

    uint from(int i) {
        return ~0ULL << (i & 63);
    }

    uint until(int i) {
        return ~0ULL >> (63 - (i & 63));
    }

    void apply(int k, bool on, uint mask) {
        if (on) data[k] |= mask;
        else data[k] &= ~mask;
    }
    
    void update(int l, int r, bool on) {
        int i = l >> 6, j = r >> 6;
        if (i == j) {
            apply(i, on, from(l) & until(r));
        } else {
            apply(i, on, from(l));
            for (int k = i + 1; k < j; ++k) apply(k, on, ~0ULL);
            apply(j, on, until(r));
        }
    }

    int count(int l, int r) {
        int c = 0;
        int i = l >> 6, j = r >> 6;
        if (i == j) {
            c = __builtin_popcountll(data[i] & (from(l) & until(r)));
        } else {
            c += __builtin_popcountll(data[i] & from(l));
            for (int k = i + 1; k < j; ++k) c += __builtin_popcountll(data[k]);
            c += __builtin_popcountll(data[j] & until(r));
        }
        return c;
    }

    bool empty() {
        for (uint mask : data) if (mask) return false;
        return true;
    }

    int prev(int i) {
        for (int k = i >> 6; k >= 0; --k, i = 63) {
            uint mask = data[k] & until(i);
            if (mask) return (k << 6) + 63 - __builtin_clzll(mask);
        }
        return n;
    }

    int next(int i) {
        for (int k = i >> 6; k < data.size(); ++k, i = 0) {
            uint mask = data[k] & from(i);
            if (mask) return (k << 6) + __builtin_ctzll(mask);
        }
        return n;
    }

    int segments() {
        int s = 0;
        for (int k = 0; k < data.size(); ++k) {
            s += __builtin_popcountll((data[k] >> 1) & ~data[k]);
            if ((data[k] & 1) and (k == 0 or (data[k - 1] >> 63) == 0)) s += 1;
        }
        return s;
    }
};
