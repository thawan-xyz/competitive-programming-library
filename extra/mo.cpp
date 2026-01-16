struct mo {
private:
    struct query {
        inline static int block_size;
        int l, r, k, block;

        query(int l, int r, int k): l(l), r(r), k(k) {
            block = l / block_size;
        }

        bool operator<(const query &other) const {
            if (block != other.block) return block < other.block;
            return ((block & 1) == 0) ? r < other.r : r > other.r;
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
