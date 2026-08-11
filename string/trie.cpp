struct trie {
    struct node {
        int pref = 0;
        int end = 0;
        array<int, 26> child = {};
    };

    vector<node> tree;

    trie(int n = 0) {
        tree.reserve(n + 1);
        tree.emplace_back();
    }

    void insert(string &s) {
        int i = 0;
        tree[0].pref++;
        for (char c : s) {
            int k = c - 'a';
            if (tree[i].child[k] == 0) {
                tree[i].child[k] = tree.size();
                tree.emplace_back();
            }
            i = tree[i].child[k];
            tree[i].pref++;
        }
        tree[i].end++;
    }

    void remove(string &s) {
        if (not contains(s)) return;
        int i = 0;
        tree[i].pref--;
        for (char c : s) {
            int k = c - 'a';
            i = tree[i].child[k];
            tree[i].pref--;
        }
        tree[i].end--;
    }

    bool contains(string &s) {
        int i = 0;
        for (char c : s) {
            int k = c - 'a';
            i = tree[i].child[k];
            if (i == 0) return false;
        }
        return tree[i].end != 0;
    }
};
