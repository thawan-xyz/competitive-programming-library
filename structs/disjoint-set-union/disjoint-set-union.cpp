struct dsu {
    vector<int> p, s;

    dsu(int n): p(n), s(n, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int a) {
        if (p[a] == a) return a;
        return p[a] = find(p[a]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (s[a] < s[b]) swap(a, b);
        p[b] = a;
        s[a] += s[b];
    }
};

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
