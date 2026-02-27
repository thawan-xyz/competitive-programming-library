struct aho_corasick {
private:
    struct node {
        int fail = 0;
        int exit = 0;
        array<int, 26> next = {};
        list<int> end;
    };

    list<node> trie;

public:
    aho_corasick(int n = 0) {
        trie.reserve(n + 5);
        trie.emplace_back();
    }

    void insert(str &s) {
        int i = 0;
        for (char c : s) {
            int j = c - 'a';
            if (trie[i].next[j] == 0) {
                trie[i].next[j] = trie.size();
                trie.emplace_back();
            }
            i = trie[i].next[j];
        }
        trie[i].end.push_back(s.size());
    }

    void build() {
        queue<int> q;
        for (int j = 0; j < 26; ++j) {
            int i = trie[0].next[j];
            if (i != 0) {
                q.push(i);
            }
        }
        while (not q.empty()) {
            int i = q.front(); q.pop();
            int f = trie[i].fail;
            if (not trie[f].end.empty()) {
                trie[i].exit = f;
            } else {
                trie[i].exit = trie[f].exit;
            }
            for (int j = 0; j < 26; ++j) {
                int c = trie[i].next[j];
                if (c != 0) {
                    trie[c].fail = trie[f].next[j];
                    q.push(c);
                } else {
                    trie[i].next[j] = trie[f].next[j];
                }
            }
        }
    }

    list<int> match(str &t) {
        list<int> p;
        int n = t.length();
        for (int i = 0, k = 0; k < n; ++k) {
            i = trie[i].next[t[k] - 'a'];
            for (int j = i; j != 0; j = trie[j].exit) {
                for (int l : trie[j].end) {
                    p.push_back(k - l + 1);
                }
            }
        }
        return p;
    }
};
