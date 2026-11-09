struct rollback_dsu {
    int c;
    vector<int> p, s, h;

    rollback_dsu(int n): c(n), p(n), s(n, 1) {
        iota(p.begin(), p.end(), 0);
    }

    int find(int a) {
        while (p[a] != a) a = p[a];
        return a;
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return h.push_back(-1), false;
        if (s[a] < s[b]) swap(a, b);
        p[b] = a, s[a] += s[b], c--;
        h.push_back(b);
        return true;
    }

    void rollback() {
        int b = h.back();
        h.pop_back();
        if (b == -1) return;
        int a = p[b];
        p[b] = b, s[a] -= s[b], c++;
    }

    int state() {
        return h.size();
    }
};
