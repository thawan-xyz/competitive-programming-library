struct disjoint_set_union {
    list<int> p;
    list<int> s;

    disjoint_set_union(int n): p(2 * n + 1), s(2 * n + 1) {
        for (int i = 1; i <= n; ++i) {
            p[i] = n + i;
            s[n + i] = 1;
        }
    }

    int find(int a) {
        if (p[a] == 0) return a;
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

    void move(int a, int b) {
        b = find(b);
        if (find(a) == b) return;
        s[find(a)]--;
        s[b]++;
        p[a] = b;
    }
};
