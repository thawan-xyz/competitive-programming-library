struct bit_set {
    static constexpr int range = 1024;
    static constexpr int size = (range + 63) / 64;

    uint word[size] = {};

    inline void insert(int x) {
        word[x >> 6] |= 1ULL << (x & 63);
    }

    inline void remove(int x) {
        word[x >> 6] &= ~(1ULL << (x & 63));
    }

    inline void insert_range(int l, int r) {
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

    inline void remove_range(int l, int r) {
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

    inline int prev(int x) const {
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

    inline int next(int x) const {
        int i = x >> 6;
        uint curr = word[i] & (~0ULL << (x & 63));
        if (curr) {
            return (i << 6) + __builtin_ctzll(curr);
        } else {
            for (int k = i + 1; k < size; ++k) if (word[k]) {
                return (k << 6) + __builtin_ctzll(word[k]);
            }
        }
        return range;
    }
};
