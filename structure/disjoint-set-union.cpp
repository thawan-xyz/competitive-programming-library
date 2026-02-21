struct disjoint_set_union {
    list<int> p;
    list<int> s;

    disjoint_set_union(int n): p(2 * n), s(2 * n) {
        for (int i = 0; i < n; ++i) {
            p[i] = n + i;
            s[n + i] = 1;
        }
    }

    int find(int a) {
        if (p[a] == 0) return a;
        return p[a] = find(p[a]);
    }

    bool same(int a, int b) {
        return find(a) == find(b);
    }

    void unite(int a, int b) {
        if (same(a, b)) return;
        a = find(a);
        b = find(b);
        if (s[a] < s[b]) swap(a, b);
        p[b] = a;
        s[a] += s[b];
    }

    void move(int a, int b) {
        if (same(a, b)) return;
        b = find(b);
        s[find(a)]--;
        s[b]++;
        p[a] = b;
    }
};
