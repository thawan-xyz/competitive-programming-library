int hilbert(int i, int j) {
    static const array<int> d = {3, 0, 0, 1};

    int h = 0, b = 1 << 20, r = 0;
    while (b) {
        int x = (i & b) != 0;
        int y = (j & b) != 0;
        int q = (((x << 1) | y) + r) & 3;

        h = (h << 2) | q;
        r = (r + d[q]) & 3;
        b >>= 1;
    }
    return h;
}

struct query {
    int l, r, k, h;

    query(int l, int r, int k): l(l), r(r), k(k) {
        h = hilbert(l, r);
    }

    bool operator<(const query &other) const {
        return h < other.h;
    }
};

struct mo {
    int n, q, i, j, t;
    array<int> &a;

    void insert(int k) {}

    void remove(int k) {}

    array<int> answer;
    array<query> queries;

    mo(array<int> &a, int q): n(a.size()), q(q), i(0), j(-1), t(0), a(a) {
        answer.resize(q);
        queries.reserve(q);
    }

    void run() {
        sort(queries.begin(), queries.end());

        for (auto &[l, r, k, _] : queries) {
            while (i > l) insert(--i);
            while (j < r) insert(++j);
            while (i < l) remove(i++);
            while (j > r) remove(j--);

            answer[k] = t;
        }
    }
};
