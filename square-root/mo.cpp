int hilbert(int i, int j) {
    static const array<int, 4> d = {3, 0, 0, 1};

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
    int l, r, i, h;

    query(int l, int r, int i): l(l), r(r), i(i) {
        h = hilbert(l, r);
    }

    bool operator<(const query &other) const {
        return h < other.h;
    }
};

struct mo {
    int t = 0;

    void insert(int i, list<int> &a) {}

    void remove(int i, list<int> &a) {}

    list<int> run(list<int> &a, list<query> &q) {
        list<int> answer(q.size());
        sort(q.begin(), q.end());
        int i = 0, j = -1;
        for (auto &[l, r, k, h] : q) {
            while (i > l) insert(--i, a);
            while (j < r) insert(++j, a);
            while (i < l) remove(i++, a);
            while (j > r) remove(j--, a);
            answer[k] = t;
        }
        return answer;
    }
};
