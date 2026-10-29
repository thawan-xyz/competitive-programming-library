// Link-Cut Tree: dynamic forest with link, cut, connected, lca, path query, path update and set
// Time: O(log N) amortized per operation | Space: O(N)
// Note: vertices are 1-based (a[0] is ignored) | lca is 0 if not connected | edit node, pull and apply
struct link_cut_tree {
    struct node {
        int val = 0, size = 0;
        int sum = 0, lazy = 0;
        bool rev = false;
        int p = 0;
        array<int, 2> c = {0, 0};
    };

    void pull(int n) {
        node &a = tree[n], &l = tree[a.c[0]], &r = tree[a.c[1]];
        a.size = l.size + 1 + r.size;
        a.sum = l.sum + a.val + r.sum;
    }

    void apply(int n, int x) {
        if (n == 0) return;
        tree[n].val += x;
        tree[n].sum += x * tree[n].size;
        tree[n].lazy += x;
    }

    vector<node> tree;

    link_cut_tree(const vector<int> &a): tree(a.size()) {
        for (int i = 1; i < a.size(); ++i) {
            tree[i].val = a[i];
            pull(i);
        }
    }

    void flip(int n) {
        if (n == 0) return;
        swap(tree[n].c[0], tree[n].c[1]);
        tree[n].rev ^= 1;
    }

    void push(int n) {
        if (tree[n].rev) flip(tree[n].c[0]), flip(tree[n].c[1]), tree[n].rev = false;
        if (tree[n].lazy != tree[0].lazy) {
            apply(tree[n].c[0], tree[n].lazy), apply(tree[n].c[1], tree[n].lazy);
            tree[n].lazy = tree[0].lazy;
        }
    }

    bool is_root(int n) {
        int p = tree[n].p;
        return tree[p].c[0] != n and tree[p].c[1] != n;
    }

    void rotate(int n) {
        int p = tree[n].p, g = tree[p].p, d = tree[p].c[1] == n;
        if (not is_root(p)) tree[g].c[tree[g].c[1] == p] = n;
        tree[n].p = g;
        tree[p].c[d] = tree[n].c[d ^ 1];
        if (tree[n].c[d ^ 1]) tree[tree[n].c[d ^ 1]].p = p;
        tree[n].c[d ^ 1] = p;
        tree[p].p = n;
        pull(p), pull(n);
    }

    void splay(int n) {
        static vector<int> s;
        s = {n};
        for (int a = n; not is_root(a); a = tree[a].p) s.push_back(tree[a].p);
        while (s.size()) push(s.back()), s.pop_back();
        while (not is_root(n)) {
            int p = tree[n].p, g = tree[p].p;
            if (not is_root(p)) rotate((tree[g].c[1] == p) == (tree[p].c[1] == n) ? p : n);
            rotate(n);
        }
    }

    int access(int a) {
        int last = 0;
        for (int x = a; x != 0; x = tree[x].p) {
            splay(x);
            tree[x].c[1] = last;
            pull(x);
            last = x;
        }
        splay(a);
        return last;
    }

    void make_root(int a) {
        access(a);
        flip(a);
    }

    int find_root(int a) {
        access(a);
        while (tree[a].c[0] != 0) push(a), a = tree[a].c[0];
        splay(a);
        return a;
    }

    void link(int a, int b) {
        make_root(a);
        if (find_root(b) != a) tree[a].p = b;
    }

    void cut(int a, int b) {
        make_root(a);
        access(b);
        if (tree[b].c[0] == a and tree[a].c[1] == 0) {
            tree[b].c[0] = tree[a].p = 0;
            pull(b);
        }
    }

    bool connected(int a, int b) {
        return find_root(a) == find_root(b);
    }

    int lca(int a, int b) {
        if (not connected(a, b)) return 0;
        access(a);
        return access(b);
    }

    void set(int a, int x) {
        access(a);
        tree[a].val = x;
        pull(a);
    }

    void update(int a, int b, int x) {
        make_root(a);
        access(b);
        apply(b, x);
    }

    node query(int a, int b) {
        make_root(a);
        access(b);
        return tree[b];
    }
};
