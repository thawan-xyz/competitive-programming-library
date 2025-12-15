struct coprime_set {
    map<int, int> n;

    array<pair<int, int>> divisors(array<int> &p) {
        int k = p.size();
        array<pair<int, int>> a; a.reserve(1 << k);
        for (int m = 0; m < (1 << k); ++m) {
            int d = 1, µ = 1;
            for (int i = 0; i < k; ++i) if (m & (1 << i)) {
                d *= p[i], µ *= -1;
            }
            a.push_back({d, µ});
        }
        return a;
    }

    void insert(array<int> &p) {
        array<pair<int, int>> a = divisors(p);
        for (auto &[d, µ] : a) {
            n[d]++;
        }
    }

    void remove(array<int> &p) {
        array<pair<int, int>> a = divisors(p);
        for (auto &[d, µ] : a) {
            n[d]--;
        }
    }

    int query(array<int> &p) {
        array<pair<int, int>> a = divisors(p);
        int t = 0;
        for (auto &[d, µ] : a) {
            t += n[d] * µ;
        }
        return t;
    }
};
