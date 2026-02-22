struct palindromic_tree {
    struct node {
        int length, fail;
        array<int, 26> child = {};

        node(int length): length(length), fail(0) {}
    };

    int suffix;
    list<char> text;
    list<node> tree;

    palindromic_tree(int n): suffix(0) {
        text.reserve(n + 5);
        text.push_back('$');
        tree.reserve(n + 5);
        tree.push_back(node(0));
        tree.push_back(node(-1));
        tree[0].fail = 1;
    }

    int follow(int id) {
        while (text[(text.size() - tree[id].length) - 2] != text.back()) {
            id = tree[id].fail;
        }
        return id;
    }

    void insert(char c) {
        text.push_back(c);
        suffix = follow(suffix);

        if (not tree[suffix].child[c - 'a']) {
            int id = tree.size();
            tree.push_back(node(tree[suffix].length + 2));

            tree[id].fail = tree[follow(tree[suffix].fail)].child[c - 'a'];
            tree[suffix].child[c - 'a'] = id;
        }
        suffix = tree[suffix].child[c - 'a'];
    }
};
