struct aho_corasick {
private:
    struct node {
        int fail;
        array<int> next, end;

        node(): fail(0), next(26), end() {}
    };

    array<node> trie;

public:
    aho_corasick(): trie(1) {}

    void insert(str &s) {
        int i = 0;
        for (char &c : s) {
            int x = c - 'a';
            if (not trie[i].next[x]) {
                trie[i].next[x] = trie.size();
                trie.push_back(node());
            }
            i = trie[i].next[x];
        }
        trie[i].end.push_back(s.size());
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < 26; ++c) {
            int i = trie[0].next[c];
            if (i) {
                q.push(i);
            }
        }
        while (q.size()) {
            int a = q.front(); q.pop();
            for (int c = 0; c < 26; ++c) {
                int b = trie[a].next[c];
                if (b) {
                    trie[b].fail = trie[trie[a].fail].next[c];
                    trie[b].end.insert(trie[b].end.end(), trie[trie[b].fail].end.begin(), trie[trie[b].fail].end.end());
                    q.push(b);
                } else {
                    trie[a].next[c] = trie[trie[a].fail].next[c];
                }
            }
        }
    }

    array<int> match(str &t) {
        array<int> a;
        int n = t.length();
        for (int i = 0, k = 0; k < n; ++k) {
            int x = t[k] - 'a';
            i = trie[i].next[x];
            for (int &l : trie[i].end) {
                a.push_back((k - l) + 1);
            }
        }
        return a;
    }
};
