struct two_sat {
    int n;
    list<list<int>> g;
    
    two_sat(int n): n(n), g(2 * n) {}

    void disjunction(int a, bool n_a, int b, bool n_b) {
        a = (2 * a) ^ n_a;
        b = (2 * b) ^ n_b;
        g[a ^ 1].push_back(b);
        g[b ^ 1].push_back(a);
    }

    list<bool> build() {
        list<list<int>> components = tarjan(g, 0);
        int m = components.size();
        list<int> id(2 * n);
        for (int i = 0; i < m; ++i) {
            for (int a : components[i]) {
                id[a] = i;
            }
        }
        list<bool> assignment(n);
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[(2 * i) ^ 1]) return {};
            assignment[i] = id[2 * i] > id[(2 * i) ^ 1];
        }
        return assignment;
    }
};
