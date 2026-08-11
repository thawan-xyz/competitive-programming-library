struct aho_corasick {
    struct node {
        int fail = 0;
        int exit = 0;
        int len = 0;
        int cnt = 0;
        array<int, 26> next = {};
    };

    vector<node> trie;

    aho_corasick(int n = 0) {
        trie.reserve(n + 5);
        trie.emplace_back();
    }

    void insert(string &s) {
        int i = 0;
        for (char c : s) {
            int k = c - 'a';
            if (trie[i].next[k] == 0) {
                trie[i].next[k] = trie.size();
                trie.emplace_back();
            }
            i = trie[i].next[k];
        }
        trie[i].len = s.length();
        trie[i].cnt++;
    }

    void compile() {
        queue<int> q;
        for (int c = 0; c < 26; ++c) {
            int i = trie[0].next[c];
            if (i != 0) q.push(i);
        }
        while (q.size()) {
            int i = q.front(); q.pop();
            int f = trie[i].fail;
            trie[i].exit = trie[f].cnt != 0 ? f : trie[f].exit;
            for (int c = 0; c < 26; ++c) {
                int &j = trie[i].next[c];
                if (j != 0) {
                    trie[j].fail = trie[f].next[c];
                    q.push(j);
                } else {
                    j = trie[f].next[c];
                }
            }
        }
    }

    vector<int> match(string &t) {
        int n = t.length();
        vector<int> p;
        int i = 0;
        for (int k = 0; k < n; ++k) {
            i = trie[i].next[t[k] - 'a'];
            for (int j = i; j != 0; j = trie[j].exit) if (trie[j].cnt != 0) {
                for (int r = 1; r <= trie[j].cnt; ++r) {
                    p.push_back(k - trie[j].len + 1);
                }
            }
        }
        return p;
    }
};
