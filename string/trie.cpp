struct trie {
    struct node {
        int pref = 0, end = 0;
        array<int, 26> child = {};
    };

    vector<node> tree = {node()};

    int find(const string &s) {
        int a = 0;
        for (char h : s) {
            int c = h - 'a';
            a = tree[a].child[c];
            if (a == 0) return -1;
        }
        return a;
    }

    void update(const string &s, int d) {
        int a = 0;
        tree[a].pref += d;
        for (char h : s) {
            int c = h - 'a';
            if (tree[a].child[c] == 0) {
                tree[a].child[c] = tree.size();
                tree.emplace_back();
            }
            a = tree[a].child[c];
            tree[a].pref += d;
        }
        tree[a].end += d;
    }
};
