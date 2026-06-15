// Coprime Set: counts elements coprime to a given number using Inclusion-Exclusion
// Time: insert/remove/query O(2^K * (K + log D)) | Space: O(N * 2^K)
// Note: P must be a vector of DISTINCT prime factors | K = size of P, D = unique divisors in map
struct coprime_set {
    map<int, int> n;

    vector<pair<int, int>> divisors(vector<int> &p) {
        int k = p.size();
        vector<pair<int, int>> a; a.reserve(1 << k);
        for (int m = 0; m < (1 << k); ++m) {
            int d = 1, mu = 1;
            for (int i = 0; i < k; ++i) if (m & (1 << i)) {
                d *= p[i], mu *= -1;
            }
            a.push_back({d, mu});
        }
        return a;
    }

    void insert(vector<int> &p) {
        vector<pair<int, int>> a = divisors(p);
        for (auto &[d, mu] : a) {
            n[d]++;
        }
    }

    void remove(vector<int> &p) {
        vector<pair<int, int>> a = divisors(p);
        for (auto &[d, mu] : a) {
            n[d]--;
        }
    }

    int query(vector<int> &p) {
        int t = 0;
        vector<pair<int, int>> a = divisors(p);
        for (auto &[d, mu] : a) {
            t += n[d] * mu;
        }
        return t;
    }
};
