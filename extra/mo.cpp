struct mo {
private:
    struct query {
        inline static int block_size;
        int l, r, k;

        bool operator<(const query &other) const {
            int a = l / block_size;
            int b = other.l / block_size;

            if (a != b) return a < b;
            return ((a & 1) == 0) ? r < other.r : r > other.r;
        }
    };

    int n, q, i, j, t;
    array<int> &a;

    void insert(int k) {}

    void remove(int k) {}

public:
    array<int> answer;
    array<query> queries;

    mo(array<int> &a, int q): n(a.size()), q(q), i(0), j(-1), t(0), a(a) {
        answer.resize(q);

        query::block_size = sqrt(n);
        queries.reserve(q);
    }

    void run() {
        sort(queries.begin(), queries.end());

        for (auto &[l, r, k] : queries) {
            while (i > l) insert(--i);
            while (j < r) insert(++j);
            while (i < l) remove(i++);
            while (j > r) remove(j--);

            answer[k] = t;
        }
    }
};
