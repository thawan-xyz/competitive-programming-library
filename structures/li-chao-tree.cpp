struct line {
    int a, b;

    int eval(int x) const {
        return a * x + b;
    }
};

struct li_chao_tree {
private:
    struct node {
        line h;
        int l, r;

        node(line h): h(h), l(0), r(0) {}
    };

    int neutral;
    int min_x, max_x;
    bool is_max;
    vector<node> tree;

    bool compare(int x, int y) {
        return is_max ? x > y : x < y;
    }

    int merge(int x, int y) {
        return is_max ? max(x, y) : min(x, y);
    }

    int insert_line(line h, int p, int l, int r) {
        if (p == 0) {
            p = tree.size();
            tree.push_back(node({0, neutral}));
        }
        int m = l + (r - l) / 2;
        bool is_l = compare(h.eval(l), tree[p].h.eval(l));
        bool is_m = compare(h.eval(m), tree[p].h.eval(m));
        if (is_m) swap(h, tree[p].h);
        if (l == r) return p;
        if (is_l != is_m) {
            int c = insert_line(h, tree[p].l, l, m);
            tree[p].l = c;
        } else {
            int c = insert_line(h, tree[p].r, m + 1, r);
            tree[p].r = c;
        }
        return p;
    }

    int insert_segment(line h, int ql, int qr, int p, int l, int r) {
        if (p == 0) {
            p = tree.size();
            tree.push_back(node({0, neutral}));
        }
        if (ql <= l and r <= qr) return insert_line(h, p, l, r);
        int m = l + (r - l) / 2;
        if (ql <= m) {
            int c = insert_segment(h, ql, qr, tree[p].l, l, m);
            tree[p].l = c;
        }
        if (qr > m) {
            int c = insert_segment(h, ql, qr, tree[p].r, m + 1, r);
            tree[p].r = c;
        }
        return p;
    }

    int query(int x, int p, int l, int r) {
        if (p == 0) return neutral;
        int y = tree[p].h.eval(x);
        if (l == r) return y;
        int m = l + (r - l) / 2;
        if (x <= m) y = merge(y, query(x, tree[p].l, l, m));
        else y = merge(y, query(x, tree[p].r, m + 1, r));
        return y;
    }

public:
    li_chao_tree(int min_x, int max_x, bool is_max): neutral(is_max ? -inf : inf), min_x(min_x), max_x(max_x), is_max(is_max) {
        tree.push_back(node({0, neutral}));
        tree.push_back(node({0, neutral}));
    }

    void insert_line(int a, int b) {
        insert_line({a, b}, 1, min_x, max_x);
    }

    void insert_segment(int a, int b, int l, int r) {
        if (l <= r) insert_segment({a, b}, l, r, 1, min_x, max_x);
    }

    int query(int x) {
        return query(x, 1, min_x, max_x);
    }
};
