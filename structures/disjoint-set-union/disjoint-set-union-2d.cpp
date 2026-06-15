struct dsu_2d {
    int n, m;
    vector<int> p, s;

    dsu_2d(int n, int m): n(n), m(m), p(n * m), s(n * m, 1) {
        for (int i = 0; i < n * m; ++i) p[i] = i;
    }

    int id(int r, int c) {
        return r * m + c;
    }

    int find(int a) {
        if (p[a] == a) return a;
        return p[a] = find(p[a]);
    }

    int find(int r, int c) {
        return find(id(r, c));
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (s[a] < s[b]) swap(a, b);
        p[b] = a;
        s[a] += s[b];
    }

    void unite(int r1, int c1, int r2, int c2) {
        unite(id(r1, c1), id(r2, c2));
    }
};
