struct trie {
private:
    struct node {
        int pref = 0;
        int end = 0;
        array<int, 26> child = {};
    };

    vector<node> tree;

    void dfs(int i, string &s, vector<string> &r) {
        if (tree[i].end != 0) {
            r.push_back(s);
        }
        for (int j = 0; j < 26; ++j) {
            if (tree[i].child[j]) {
                s.push_back(j + 'a');
                dfs(tree[i].child[j], s, r);
                s.pop_back();
            }
        }
    }

public:
    trie() {
        tree.emplace_back();
    }

    void insert(string &s) {
        int i = 0;
        tree[0].pref++;
        for (char c : s) {
            int j = c - 'a';
            if (tree[i].child[j] == 0) {
                tree[i].child[j] = tree.size();
                tree.emplace_back();
            }
            i = tree[i].child[j];
            tree[i].pref++;
        }
        tree[i].end++;
    }

    void remove(string &s) {
        int i = 0;
        for (char c : s) {
            int j = c - 'a';
            if (tree[i].child[j] == 0) {
                return;
            }
            i = tree[i].child[j];
        }
        if (tree[i].end == 0) return;
        int p = 0;
        tree[0].pref--;
        for (char c : s) {
            int j = c - 'a';
            i = tree[p].child[j];
            tree[i].pref--;
            if (tree[i].pref == 0) {
                tree[p].child[j] = 0;
                return;
            }
            p = i;
        }
        tree[p].end--;
    }

    bool search(string &s) {
        int i = 0;
        for (char c : s) {
            int j = c - 'a';
            if (tree[i].child[j] == 0) {
                return false;
            }
            i = tree[i].child[j];
        }
        return tree[i].end != 0;
    }

    vector<string> complete(string s) {
        int i = 0;
        vector<string> r;
        for (char c : s) {
            int j = c - 'a';
            if (tree[i].child[j] == 0) {
                return r;
            }
            i = tree[i].child[j];
        }
        dfs(i, s, r);
        return r;
    }
};
