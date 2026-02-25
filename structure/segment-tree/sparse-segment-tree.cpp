struct sparse_segment_tree {
private:
    struct node {
        int x = 0;
        int l = 0, r = 0;
    };

    array<int, 3> root;
    list<node> tree;

    int modify(int i, int x, int p, int l, int r) {
        if (i < l or r < i) return p;

        if (not p) {
            p = tree.size();
            tree.emplace_back();
        }

        if (l == r) {
            tree[p].x += x;
            return p;
        }

        int m = l + (r - l) / 2;
        tree[p].l = modify(i, x, tree[p].l, l, m);
        tree[p].r = modify(i, x, tree[p].r, m + 1, r);
        tree[p].x = tree[tree[p].l].x + tree[tree[p].r].x;
        return p;
    }

    int query(int ql, int qr, int p, int l, int r) {
        if (not p or (qr < l or r < ql)) return 0;

        if (ql <= l and r <= qr) return tree[p].x;

        int m = l + (r - l) / 2;
        return query(ql, qr, tree[p].l, l, m) + query(ql, qr, tree[p].r, m + 1, r);
    }

public:
    sparse_segment_tree(int l, int r) {
        root = {0, l, r};
        tree.reserve(2e5);
        tree.emplace_back();
    }

    void modify(int i, int x) {
        root[0] = modify(i, x, root[0], root[1], root[2]);
    }

    int query(int ql, int qr) {
        return query(ql, qr, root[0], root[1], root[2]);
    }
};
