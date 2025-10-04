struct palindromic_tree {
    struct node {
        int length, link;
        array<int> child;

        node(int length): length(length), link(0), child(26) {}
    };

    int suffix;
    array<char> text;
    array<node> tree;

    palindromic_tree(int n): suffix(0) {
        text.reserve(n + 5);
        text.push_back('$');
        tree.reserve(n + 5);
        tree.push_back(node(0));
        tree.push_back(node(-1));
        tree[0].link = 1;
    }

    int follow(int id) {
        while (text[(text.size() - tree[id].length) - 2] != text.back()) id = tree[id].link;
        return id;
    }

    void insert(char c) {
        text.push_back(c);
        suffix = follow(suffix);

        if (not tree[suffix].child[c - 'a']) {
            int id = tree.size();
            tree.push_back(node(tree[suffix].length + 2));

            tree[id].link = tree[follow(tree[suffix].link)].child[c - 'a'];
            tree[suffix].child[c - 'a'] = id;
        }
        suffix = tree[suffix].child[c - 'a'];
    }
};
