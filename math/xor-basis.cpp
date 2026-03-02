struct xor_basis {
    static constexpr int log = 30;
    int n = 0, size = 0;
    array<int, log> basis = {};
    vector<int> reduced;

    bool insert(int x) {
        n += 1;
        for (int i = log - 1; i >= 0; --i) if ((x >> i) & 1) {
            if (basis[i] == 0) {
                basis[i] = x;
                size += 1;
                return true;
            } else {
                x ^= basis[i];
            }
        }
        return false;
    }

    void reduce() {
        reduced.clear();
        for (int i = log - 1; i >= 0; --i) if (basis[i] != 0) {
            for (int j = i - 1; j >= 0; --j) if (((basis[i] >> j) & 1) and basis[j] != 0) {
                basis[i] ^= basis[j];
            }
            reduced.push_back(basis[i]);
        }
        reverse(reduced.begin(), reduced.end());
    }

    int kth(int k) {
        if ((k >> reduced.size()) != 0) return -1;
        int x = 0;
        for (int i = 0; i < size; ++i) if ((k >> i) & 1) {
            x ^= reduced[i];
        }
        return x;
    }
};
