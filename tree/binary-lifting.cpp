struct xyz {
    int n, log;
    array<array<int>> &graph;
    array<int> depth;
    array<array<int>> up;

    binary_lifting(array<array<int>> &graph, int root = 1): n(graph.size()), log(31 - __builtin_clz(n)), graph(graph), depth(n + 1), up(n + 1, array<int>(log + 1)) {
        depth[root] = 0;
        build(root, 0);
    }

    void build(int a, int p) {
        up[a][0] = p;
        for (int i = 1; i <= log; ++i) {
            up[a][i] = up[up[a][i - 1]][i - 1];
        }

        for (int b : graph[a]) if (b != p) {
            depth[b] = depth[a] + 1;
            build(b, a);
        }
    }

    int kth_ancestor(int a, int k) {
        if (depth[a] < k) return -1;

        for (int i = log; i >= 0; --i) {
            if (k & (1 << i)) {
                a = up[a][i];
            }
        }
        return a;
    }

    int lowest_common_ancestor(int a, int b) {
        if (depth[a] > depth[b]) swap(a, b);
        a = kth_ancestor(a, depth[b] - depth[a]);

        if (a == b) return a;
        for (int i = log; i >= 0; --i) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i], b = up[b][i];
            }
        }
        return up[a][0];
    }
};
