// Li Chao Tree: dynamic line & segment container for maximum convex hull trick
// Time: line insert/query O(log U) | segment insert O(log^2 U) | Space: O(N log U)
// Note: computes max(ax + b) | for min: insert (-a, -b) and take -query(x)
struct li_chao_tree {
private:
    struct line {
        int a, b;

        int operator()(int x) const {
            return a * x + b;
        }
    };

    struct node {
        line f;
        int l, r;
    };

    int min_x, max_x;
    vector<node> tree;

    int create_node() {
        tree.push_back({{0, -inf}, 0, 0});
        return tree.size() - 1;
    }

    int insert_line(line f, int p, int l, int r) {
        if (p == 0) p = create_node();
        int m = l + (r - l) / 2;
        bool is_l = f(l) > tree[p].f(l);
        bool is_m = f(m) > tree[p].f(m);
        if (is_m) swap(f, tree[p].f);
        if (l == r) return p;
        if (is_l != is_m) tree[p].l = insert_line(f, tree[p].l, l, m);
        else tree[p].r = insert_line(f, tree[p].r, m + 1, r);
        return p;
    }

    int insert_segment(line f, int ql, int qr, int p, int l, int r) {
        if (p == 0) p = create_node();
        if (ql <= l and r <= qr) return insert_line(f, p, l, r);
        int m = l + (r - l) / 2;
        if (ql <= m) tree[p].l = insert_segment(f, ql, qr, tree[p].l, l, m);
        if (qr > m) tree[p].r = insert_segment(f, ql, qr, tree[p].r, m + 1, r);
        return p;
    }

    int query(int x, int p, int l, int r) {
        if (p == 0) return -inf;
        int y = tree[p].f(x);
        if (l == r) return y;
        int m = l + (r - l) / 2;
        if (x <= m) y = max(y, query(x, tree[p].l, l, m));
        else y = max(y, query(x, tree[p].r, m + 1, r));
        return y;
    }

public:
    li_chao_tree(int min_x, int max_x): min_x(min_x), max_x(max_x) {
        tree.push_back({{0, -inf}, 0, 0});
        create_node();
    }

    void insert_line(int a, int b) {
        insert_line({a, b}, 1, min_x, max_x);
    }

    void insert_segment(int a, int b, int l, int r) {
        insert_segment({a, b}, l, r, 1, min_x, max_x);
    }

    int query(int x) {
        return query(x, 1, min_x, max_x);
    }
};
