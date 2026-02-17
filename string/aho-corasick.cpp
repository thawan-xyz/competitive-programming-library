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
        for (char &c : s) {
            if (trie[i].next[c - 'a'] == 0) {
                trie[i].next[c - 'a'] = trie.size();
                trie.emplace_back();
            }
            i = trie[i].next[c - 'a'];
        }
        trie[i].end.push_back(s.size());
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < 26; ++c) {
            int i = trie[0].next[c];
            if (i != 0) {
                q.push(i);
            }
        }
        while (q.size()) {
            int a = q.front(); q.pop();
            int f = trie[a].fail;
            if (trie[f].end.empty()) {
                trie[a].exit = trie[f].exit;
            } else {
                trie[a].exit = f;
            }
            for (int c = 0; c < 26; ++c) {
                int b = trie[a].next[c];
                if (b != 0) {
                    trie[b].fail = trie[trie[a].fail].next[c];
                    q.push(b);
                } else {
                    trie[a].next[c] = trie[trie[a].fail].next[c];
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
