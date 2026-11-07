// XOR Basis: reduced basis of the inserted numbers, answering questions about the xors of their subsets
// Time: O(bits) per operation | Space: O(bits)
// Note: basis[i] has highest bit i and no other pivot bit | kth(k) = k-th smallest distinct subset xor, from 0 | [k] counts all 2^n subsets, with repeats | max(x) = largest x ^ subset xor
struct xor_basis {
    static const int bits = 60;
    int n = 0, r = 0;
    array<int, bits> basis = {};

    bool insert(int x) {
        n++;
        for (int i = bits - 1; i >= 0; --i) {
            if (x >> i & 1 and basis[i] != 0) x ^= basis[i];
        }
        if (x == 0) return false;
        int p = __lg(x);
        for (int i = p + 1; i < bits; ++i) {
            if (basis[i] >> p & 1) basis[i] ^= x;
        }
        basis[p] = x, r++;
        return true;
    }

    bool contains(int x) {
        for (int i = bits - 1; i >= 0; --i) {
            if (x >> i & 1) x ^= basis[i];
        }
        return x == 0;
    }

    int max(int x = 0) {
        for (int i = bits - 1; i >= 0; --i) {
            if (not (x >> i & 1)) x ^= basis[i];
        }
        return x;
    }

    int kth(int k) {
        if (k >> r != 0) return -1;
        int x = 0;
        for (int i = 0; i < bits; ++i) {
            if (basis[i] == 0) continue;
            if (k & 1) x ^= basis[i];
            k >>= 1;
        }
        return x;
    }

    int operator[](int k) {
        return n - r >= 63 ? 0 : kth(k >> (n - r));
    }

    int ways(int x) {
        return contains(x) ? mod_pow(2, n - r, mod) : 0;
    }
};

// XOR Basis: reduced basis of the inserted bits-bit numbers, answering questions about the xors of their subsets
// Time: O(bits^2 / 64) per operation | Space: O(bits^2 / 64)
// Note: basis[i] has highest bit i and no other pivot bit | kth(k) = k-th smallest distinct subset xor, from 0, needs k < 2^r | [k] counts all 2^n subsets, with repeats | max(x) = largest x ^ subset xor
template<int bits>
struct xor_basis {
    int n = 0, r = 0;
    vector<bitset<bits>> basis = vector<bitset<bits>>(bits);

    bool insert(bitset<bits> x) {
        n++;
        for (int i = bits - 1; i >= 0; --i) {
            if (x[i] and basis[i][i]) x ^= basis[i];
        }
        if (x.none()) return false;
        int p = bits - 1;
        while (not x[p]) p--;
        for (int i = p + 1; i < bits; ++i) {
            if (basis[i][p]) basis[i] ^= x;
        }
        basis[p] = x, r++;
        return true;
    }

    bool contains(bitset<bits> x) {
        for (int i = bits - 1; i >= 0; --i) {
            if (x[i] and basis[i][i]) x ^= basis[i];
        }
        return x.none();
    }

    bitset<bits> max(bitset<bits> x = {}) {
        for (int i = bits - 1; i >= 0; --i) {
            if (not x[i] and basis[i][i]) x ^= basis[i];
        }
        return x;
    }

    bitset<bits> kth(bitset<bits> k) {
        bitset<bits> x;
        for (int i = 0, j = 0; i < bits; ++i) {
            if (basis[i][i] and k[j++]) x ^= basis[i];
        }
        return x;
    }

    bitset<bits> operator[](int k) {
        return kth(n - r >= 63 ? 0 : k >> (n - r));
    }

    int ways(bitset<bits> x) {
        return contains(x) ? mod_pow(2, n - r, mod) : 0;
    }
};
