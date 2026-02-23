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
        int n = 0;
        tree[0].prefix++;

        for (char &c : s) {
            if (not tree[n].child[c - 'a']) {
                tree[n].child[c - 'a'] = tree.size();
                tree.emplace_back();
            }
            n = tree[n].child[c - 'a'];
            tree[n].prefix++;
        }
        tree[n].end++;
    }

    void remove(str &s) {
        int n = 0;
        list<int> path = {0};

        for (char &c : s) {
            if (not tree[n].child[c - 'a']) {
                return;
            }
            n = tree[n].child[c - 'a'];
            path.push_back(n);
        }

        if (tree[n].end == 0) return;
        tree[n].end--;

        for (int i = path.size() - 1; i >= 1; --i) {
            n = path[i];
            tree[n].prefix--;

            int p = path[i - 1];
            if (tree[n].prefix == 0) {
                tree[p].child[s[i - 1] - 'a'] = 0;
            }
        }
        tree[0].prefix--;
    }

    bool search(str &s) {
        int n = 0;

        for (char &c : s) {
            if (not tree[n].child[c - 'a']) {
                return false;
            }
            n = tree[n].child[c - 'a'];
        }
        return tree[n].end != 0;
    }

    list<str> complete(str &s) {
        int n = 0;
        list<str> r;

        for (char &c : s) {
            if (not tree[n].child[c - 'a']) {
                return r;
            }
            n = tree[n].child[c - 'a'];
        }
        dfs(n, s, r);
        return r;
    }

    void dfs(int n, str &s, list<str> &r) {
        if (tree[n].end != 0) {
            r.push_back(s);
        }

        for (int i = 0; i < 26; ++i) {
            if (tree[n].child[i]) {
                s.push_back(i + 'a');
                dfs(tree[n].child[i], s, r);
                s.pop_back();
            }
        }
    }
};
