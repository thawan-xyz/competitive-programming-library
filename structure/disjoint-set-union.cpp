struct disjoint_set_union {
    vector<int> p, s;

    disjoint_set_union(int n): p(n), s(n, 1) {
        for (int i = 0; i < n; ++i) p[i] = i;
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
