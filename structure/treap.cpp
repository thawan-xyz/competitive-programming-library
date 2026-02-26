struct treap {
private:
    struct node {
        int x = 0, y = 0;
        int l = 0, r = 0;
        int s = 1;
    };

    int make(int x, int y) {
        int i = tree.size();
        tree.emplace_back();
        tree[i].x = x;
        tree[i].y = y;
        return i;
    }

    int size(int i) {
        return i ? tree[i].s : 0;
    }

    void update(int i) {
        tree[i].s = 1 + size(tree[i].l) + size(tree[i].r);
    }

    pair<int, int> split(int i, int x) {
        if (not i) return {0, 0};

        if (tree[i].x <= x) {
            auto [l, r] = split(tree[i].r, x);
            tree[i].r = l;
            update(i);
            return {i, r};
        } else {
            auto [l, r] = split(tree[i].l, x);
            tree[i].l = r;
            update(i);
            return {l, i};
        }
    }

    int merge(int l, int r) {
        if (not l) return r;
        if (not r) return l;

        if (tree[l].y > tree[r].y) {
            tree[l].r = merge(tree[l].r, r);
            update(l);
            return l;
        } else {
            tree[r].l = merge(l, tree[r].l);
            update(r);
            return r;
        }
    }

    int insert(int i, int x, int y) {
        if (not i) return make(x, y);

        if (tree[i].y < y) {
            auto [l, r] = split(i, x);
            i = make(x, y);
            tree[i].l = l;
            tree[i].r = r;
        } else {
            if (x <= tree[i].x) tree[i].l = insert(tree[i].l, x, y);
            if (x > tree[i].x) tree[i].r = insert(tree[i].r, x, y);
        }
        update(i);
        return i;
    }

    int erase(int i, int x) {
        if (not i) return 0;

        if (x == tree[i].x) return merge(tree[i].l, tree[i].r);
        if (x < tree[i].x) tree[i].l = erase(tree[i].l, x);
        if (x > tree[i].x) tree[i].r = erase(tree[i].r, x);
        update(i);
        return i;
    }

    int index(int i, int x) {
        if (not i) return -1;

        if (x == tree[i].x) return size(tree[i].l);
        if (x < tree[i].x) return index(tree[i].l, x);

        int r = index(tree[i].r, x);
        if (r == -1) return -1;
        return 1 + size(tree[i].l) + r;
    }

    int kth(int i, int x) {
        if (not i) return -1;

        int l = size(tree[i].l);
        if (x == l) return tree[i].x;

        if (x < l) return kth(tree[i].l, x);
        return kth(tree[i].r, x - (l + 1));
    }

public:
    list<node> tree;
    int root;

    treap() {
        root = make(0, 0);
    }

    void insert(int x) {
        int y = random;
        root = insert(root, x, y);
    }

    void erase(int x) {
        root = erase(root, x);
    }

    int index(int x) {
        return index(root, x);
    }

    int kth(int i) {
        return kth(root, i);
    }

    int unite(int i, int j) {
        if (not i) return j;
        if (not j) return i;

        if (tree[i].y < tree[j].y) swap(i, j);
        auto [l, r] = split(j, tree[i].x);

        tree[i].l = unite(tree[i].l, l);
        tree[i].r = unite(tree[i].r, r);
        update(i);
        return i;
    }
};
