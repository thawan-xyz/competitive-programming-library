// Suffix Automaton: smallest automaton that reads every substring of s
// Time: O(26 N) | Space: O(26 N)
// Note: root = 1 | each state groups substrings with the same end positions
struct suffix_automaton {
    struct node {
        int len = 0, pos = -1;
        int link = 0, cnt = 0;
        array<int, 26> next = {};
    };

    int last = 1;
    vector<node> tree = {node(), node()};

    void extend(char h) {
        int c = h - 'a', cur = tree.size(), i = last;
        tree.push_back({tree[last].len + 1, tree[last].len, 1, 1});
        last = cur;
        while (i != 0 and tree[i].next[c] == 0) {
            tree[i].next[c] = cur;
            i = tree[i].link;
        }
        if (i == 0) return;
        int j = tree[i].next[c];
        if (tree[i].len + 1 == tree[j].len) {
            tree[cur].link = j;
            return;
        }
        int clone = tree.size();
        tree.push_back(tree[j]);
        tree[clone].len = tree[i].len + 1;
        tree[clone].cnt = 0;
        while (i != 0 and tree[i].next[c] == j) {
            tree[i].next[c] = clone;
            i = tree[i].link;
        }
        tree[cur].link = tree[j].link = clone;
    }

    int find(const string &t) {
        int i = 1;
        for (char h : t) {
            int c = h - 'a';
            i = tree[i].next[c];
        }
        return i;
    }

    void count_occurrences() {
        vector<int> ord(tree.size() - 2); iota(ord.begin(), ord.end(), 2);
        sort(ord.rbegin(), ord.rend(), [&](int i, int j) {return tree[i].len < tree[j].len;});
        for (int i : ord) {
            tree[tree[i].link].cnt += tree[i].cnt;
        }
    }

    int distinct_substrings() {
        int dist = 0;
        for (int i = 2; i < tree.size(); ++i) {
            dist += tree[i].len - tree[tree[i].link].len;
        }
        return dist;
    }
};
