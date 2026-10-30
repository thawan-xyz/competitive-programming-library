struct aho_corasick {
    struct node {
        int len = 0, end = 0;
        int fail = 0, exit = 0;
        array<int, 26> next = {};
    };

    vector<node> tree = {node()};
    vector<int> order;

    int insert(const string &s) {
        int a = 0;
        for (char h : s) {
            int c = h - 'a';
            if (tree[a].next[c] == 0) {
                tree[a].next[c] = tree.size();
                tree.emplace_back();
            }
            a = tree[a].next[c];
        }
        tree[a].end++;
        return a;
    }

    void build() {
        order = {0};
        for (int i = 0; i < order.size(); ++i) {
            int a = order[i], f = tree[a].fail;
            tree[a].exit = (tree[f].end > 0) ? f : tree[f].exit;
            for (int c = 0; c < 26; ++c) {
                int b = tree[a].next[c];
                if (b == 0) {
                    tree[a].next[c] = tree[f].next[c];
                } else {
                    tree[b].fail = (a == 0) ? 0 : tree[f].next[c];
                    tree[b].len = tree[a].len + 1;
                    order.push_back(b);
                }
            }
        }
    }

    vector<array<int, 2>> match(const string &t) {
        vector<array<int, 2>> p;
        int a = 0;
        for (int i = 0; i < t.size(); ++i) {
            a = tree[a].next[t[i] - 'a'];
            for (int b = a; b != 0; b = tree[b].exit) {
                if (tree[b].end > 0) p.push_back({i - tree[b].len + 1, b});
            }
        }
        return p;
    }
};
