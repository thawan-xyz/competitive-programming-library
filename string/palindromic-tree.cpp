struct palindromic_tree {
    struct node {
        int length, link;
        array<int> next;

        node(int length): length(length), link(0), next(26) {}
    };

    str s;
    array<node> tree;
    int last;

    palindromic_tree(int n): last(1) {
        s.reserve(n + 5);
        s.push_back('$');
        tree.reserve(n + 5);
        tree.push_back(node(-1));
        tree.push_back(node(0));
        tree[1].link = 0;
    }

    int suffix(int i) {
        while (s[(s.size() - tree[i].length) - 2] != s.back()) i = tree[i].link;
        return i;
    }

    void insert(char c) {
        s.push_back(c);
        last = suffix(last);

        if (not tree[last].next[c - 'a']) {
            int curr = tree.size();
            tree.push_back(node(tree[last].length + 2));

            tree[curr].link = tree[suffix(tree[last].link)].next[c - 'a'];
            tree[last].next[c - 'a'] = curr;
        }
        last = tree[last].next[c - 'a'];
    }
};
