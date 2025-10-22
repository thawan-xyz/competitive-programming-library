template <typename T>
struct sparse_table {
    int n;
    list<list<T>> table;
    F compare;
    list<int> pow2, log2;

    sparse_table(list<T> &base): n(base.size()), pow2(n + 1), log2(n + 1) {
        pow2[0] = 1;
        pow2[1] = 2;
        for (int i = 2; i <= n; ++i) {
            pow2[i] = pow2[i - 1] << 1;
            log2[i] = log2[i >> 1] + 1;
        }
        table.assign(n, list<T>(log2[n] + 1));
        for (int i = 0; i < n; ++i) {
            table[i][0] = base[i];
        }
        for (int k = 1; k <= log2[n]; ++k) {
            for (int i = 0; (i + pow2[k]) - 1 < n; ++i) {
                const T &x = table[i][k - 1];
                const T &y = table[i + pow2[k - 1]][k - 1];
                table[i][k] = compare(x, y);
            }
        }
    }

    T query(int l, int r) {
        int k = log2[(r - l) + 1];
        const T &x = table[l][k];
        const T &y = table[(r - pow2[k]) + 1][k];
        return compare(x, y);
    }
};
