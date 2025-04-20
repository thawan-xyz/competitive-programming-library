struct trie {
    struct node {
        array<int> child = array<int>(26);
        bool end = false;
        int sub = 0;
    };

    int id = 1;
    array<node> tree = array<node>(1);

    void insert(str &s) {
        int n = 0;

        for (char &c : s) {
            tree[n].sub++;
            if (not tree[n].child[c - 'a']) {
                tree.push_back(node());
                tree[n].child[c - 'a'] = id++;
            }
            n = tree[n].child[c - 'a'];
        }
        tree[n].end = true;
    }

    void remove(str &s) {
        int n = 0;
        array<int> path;
        path.push_back(0);

        for (char &c : s) {
            if (not tree[n].child[c - 'a']) {
                return;
            }
            n = tree[n].child[c - 'a'];
            path.push_back(n);
        }

        if (not tree[n].end) return;
        tree[n].end = false;

        for (int i = path.size() - 1; i >= 1; --i) {
            int p = path[i - 1], c = path[i];
            tree[c].sub--;
            if (tree[c].sub == 0 and not tree[c].end) {
                tree[p].child[s[i - 1] - 'a'] = 0;
            }
        }
        tree[0].sub--;
    }
    
    bool search(str &s) {
        int n = 0;

        for (char &c : s) {
            if (not tree[n].child[c - 'a']) {
                return false;
            }
            n = tree[n].child[c - 'a'];
        }
        return tree[n].end;
    }
    
    array<str> complete(str &s) {
        int n = 0;
        array<str> r;

        for (char &c : s) {
            if (not tree[n].child[c - 'a']) {
                return r;
            }
            n = tree[n].child[c - 'a'];
        }
        dfs(n, s, r);
        return r;
    }

    void dfs(int n, str &s, array<str> &r) {
        if (tree[n].end) {
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
