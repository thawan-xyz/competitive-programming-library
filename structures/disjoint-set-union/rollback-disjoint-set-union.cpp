struct rollback_dsu {
    int c;
    vector<int> p, s;
    vector<pair<int, int>> h;

    rollback_dsu(int n): c(n), p(n), s(n, 1) {
        for (int i = 0; i < n; ++i) p[i] = i;
    }

    int find(int a) {
        while (p[a] != a) a = p[a];
        return a;
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            h.push_back({-1, -1});
        } else {
            if (s[a] < s[b]) swap(a, b);
            h.push_back({a, b});
            c--;
            p[b] = a;
            s[a] += s[b];
        }
    }

    void rollback() {
        assert(h.size());
        auto [a, b] = h.back(); h.pop_back();
        if (a != -1) {
            c++;
            p[b] = b;
            s[a] -= s[b];
        }
    }

    int state() {
        return h.size();
    }
};
