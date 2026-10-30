struct trie {
    struct node {
        int pref = 0, end = 0;
        array<int, 26> child = {};
    };

    vector<node> tree = {node()};

    int find(const string &s) {
        int i = 0;
        for (char c : s) {
            i = tree[i].child[c - 'a'];
            if (i == 0) return -1;
        }
        return i;
    }

    void update(const string &s, int d) {
        int i = 0;
        tree[i].pref += d;
        for (char c : s) {
            int k = c - 'a';
            if (tree[i].child[k] == 0) {
                tree[i].child[k] = tree.size();
                tree.emplace_back();
            }
            i = tree[i].child[k];
            tree[i].pref += d;
        }
        tree[i].end += d;
    }
};
