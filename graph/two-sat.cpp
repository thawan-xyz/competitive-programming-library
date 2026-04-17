// 2-SAT: Solves Boolean Satisfiability for 2-CNF Formulas
// Time: Build O(N + M) | Space: O(N + M)
// Note: Uses Tarjan's SCC | 0-indexed variables
struct two_sat {
    int n;
    vector<vector<int>> g;
    
    two_sat(int n): n(n), g(2 * n) {}

    // A or B
    void disjunction(int a, bool n_a, int b, bool n_b) {
        a = (2 * a) ^ n_a;
        b = (2 * b) ^ n_b;
        g[a ^ 1].push_back(b);
        g[b ^ 1].push_back(a);
    }

    // A and B
    void conjunction(int a, bool n_a, int b, bool n_b) {
        disjunction(a, n_a, a, n_a);
        disjunction(b, n_b, b, n_b);
    }

    // A -> B
    void implication(int a, bool n_a, int b, bool n_b) {
        disjunction(a, !n_a, b, n_b);
    }

    // A == B
    void equal(int a, bool n_a, int b, bool n_b) {
        implication(a, n_a, b, n_b);
        implication(b, n_b, a, n_a);
    }

    // A != B / A xor B
    void not_equal(int a, bool n_a, int b, bool n_b) {
        disjunction(a, n_a, b, n_b);
        disjunction(a, !n_a, b, !n_b);
    }

    // Solves the 2-SAT and returns a valid assignment, or empty if unsatisfiable
    vector<bool> build() {
        vector<vector<int>> components = tarjan(g, 0);
        int m = components.size();
        vector<int> id(2 * n);
        for (int i = 0; i < m; ++i) {
            for (int a : components[i]) {
                id[a] = i;
            }
        }
        vector<bool> assignment(n);
        for (int i = 0; i < n; ++i) {
            if (id[2 * i] == id[(2 * i) ^ 1]) return {};
            assignment[i] = id[2 * i] > id[(2 * i) ^ 1];
        }
        return assignment;
    }
};
