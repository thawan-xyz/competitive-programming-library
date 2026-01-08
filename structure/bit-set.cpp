struct bit_set {
    static constexpr int size = 1024;
    static constexpr int n = (size + 63) / 64;

    uint word[n] = {};

    bool contains(int x) {
        return word[x >> 6] & (1ULL << (x & 63));
    }

    void insert(int x) {
        word[x >> 6] |= 1ULL << (x & 63);
    }

    void remove(int x) {
        word[x >> 6] &= ~(1ULL << (x & 63));
    }

    bool empty() {
        for (int i = 0; i < n; ++i) {
            if (word[i]) return false;
        }
        return true;
    }

    void insert_range(int l, int r) {
        int i = l >> 6;
        int j = r >> 6;
        if (i == j) {
            word[i] |= (~0ULL << (l & 63)) & (~0ULL >> (63 - (r & 63)));
        } else {
            word[i] |= ~0ULL << (l & 63);
            for (int k = i + 1; k < j; ++k) {
                word[k] = ~0ULL;
            }
            word[j] |= ~0ULL >> (63 - (r & 63));
        }
    }

    void remove_range(int l, int r) {
        int i = l >> 6;
        int j = r >> 6;
        if (i == j) {
            word[i] &= ~((~0ULL << (l & 63)) & (~0ULL >> (63 - (r & 63))));
        } else {
            word[i] &= ~(~0ULL << (l & 63));
            for (int k = i + 1; k < j; ++k) {
                word[k] = 0;
            }
            word[j] &= ~(~0ULL >> (63 - (r & 63)));
        }
    }

    int prev(int x) {
        int i = x >> 6;
        uint curr = word[i] & (~0ULL >> (63 - (x & 63)));
        if (curr) {
            return (i << 6) + (63 - __builtin_clzll(curr));
        } else {
            for (int k = i - 1; k >= 0; --k) if (word[k]) {
                return (k << 6) + (63 - __builtin_clzll(word[k]));
            }
        }
        return -1;
    }

    int next(int x) {
        int i = x >> 6;
        uint curr = word[i] & (~0ULL << (x & 63));
        if (curr) {
            return (i << 6) + __builtin_ctzll(curr);
        } else {
            for (int k = i + 1; k < n; ++k) if (word[k]) {
                return (k << 6) + __builtin_ctzll(word[k]);
            }
        }
        return size;
    }

    int segments() {
        int total = 0;
        for (int i = 0; i < n; ++i) {
            int count = __builtin_popcountll((word[i] >> 1) & ~word[i]);
            if ((word[i] & 1ULL) and (i == 0 or not (word[i - 1] & (1ULL << 63)))) count += 1;
            total += count;
        }
        return total;
    }
};
