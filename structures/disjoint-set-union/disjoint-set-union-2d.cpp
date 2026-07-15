struct dsu_2d {
    int n, m;
    dsu d;

    dsu_2d(int n, int m): n(n), m(m), d(n * m) {}

    int id(int r, int c) {
        return r * m + c;
    }

    int find(int r, int c) {
        return d.find(id(r, c));
    }

    void unite(int r1, int c1, int r2, int c2) {
        d.unite(id(r1, c1), id(r2, c2));
    }
};
