// 2-SAT: finds values for n boolean variables that satisfy clauses on two literals
// Time: O(n + m) | Space: O(n + m)
// Note: requires tarjan | literal ~a means not a | solve returns the values, or empty if impossible
struct two_sat {
    int n;
    vector<vector<int>> g;

    two_sat(int n): n(n), g(2 * n) {}

    int id(int a) {
        return a >= 0 ? 2 * a : 2 * ~a + 1;
    }

    void disjunction(int a, int b) {
        a = id(a), b = id(b);
        g[a ^ 1].push_back(b);
        g[b ^ 1].push_back(a);
    }

    void conjunction(int a, int b) {
        disjunction(a, a), disjunction(b, b);
    }

    void implication(int a, int b) {
        disjunction(~a, b);
    }

    void equal(int a, int b) {
        implication(a, b), implication(b, a);
    }

    void not_equal(int a, int b) {
        disjunction(a, b), disjunction(~a, ~b);
    }

    vector<bool> solve() {
        vector<int> comp = tarjan(g);
        vector<bool> x(n);
        for (int i = 0; i < n; ++i) {
            if (comp[2 * i] == comp[2 * i + 1]) return {};
            x[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return x;
    }
};
