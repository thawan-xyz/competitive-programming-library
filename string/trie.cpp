struct trie {
    struct node {
        int prefix = 0;
        int end = 0;
        array<int, 26> child = {};
    };

    list<node> tree;

    trie() {
        tree.emplace_back();
    }

    void insert(str &s) {
        int i = 0;
        tree[0].prefix++;
        for (char c : s) {
            int j = c - 'a';
            if (tree[i].child[j] == 0) {
                tree[i].child[j] = tree.size();
                tree.emplace_back();
            }
            i = tree[i].child[j];
            tree[i].prefix++;
        }
        tree[i].end++;
    }

    void remove(str &s) {
        int i = 0;
        list<int> path = {0};

        for (char c : s) {
            int j = c - 'a';
            if (tree[i].child[j] == 0) {
                return;
            }
            i = tree[i].child[j];
            path.push_back(i);
        }

        if (tree[i].end == 0) return;
        tree[i].end--;

        for (int k = path.size() - 1; k >= 1; --k) {
            i = path[k];
            tree[i].prefix--;

            int p = path[k - 1];
            if (tree[i].prefix == 0) {
                tree[p].child[s[k - 1] - 'a'] = 0;
            }
        }
        tree[0].prefix--;
    }

    bool search(str &s) {
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

    list<str> complete(str &s) {
        int i = 0;
        list<str> r;
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

    void dfs(int i, str &s, list<str> &r) {
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
};
