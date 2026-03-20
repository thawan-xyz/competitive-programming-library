// Treap: Randomized Binary Search Tree (Split/Merge)
// Time: Operations O(log N) average | Space: O(N)
// Note: Combines BST and Heap Properties | Requires mt19937 for Priorities
struct treap {
    struct node {
        int x, y, l, r, s;
    };

    int root = 0;
    vector<node> tree = {{}};

    int make(int x, int y) {
        tree.push_back({x, y, 0, 0, 1});
        return tree.size() - 1;
    }

    void update(int i) {
        tree[i].s = 1 + tree[tree[i].l].s + tree[tree[i].r].s;
    }

    void split(int i, int x, int &l, int &r) {
        if (i == 0) l = r = 0;
        else if (tree[i].x <= x) split(tree[i].r, x, tree[i].r, r), l = i, update(i);
        else split(tree[i].l, x, l, tree[i].l), r = i, update(i);
    }

    int merge(int l, int r) {
        if (l == 0 or r == 0) return l | r;
        if (tree[l].y > tree[r].y) return tree[l].r = merge(tree[l].r, r), update(l), l;
        return tree[r].l = merge(l, tree[r].l), update(r), r;
    }

    void insert(int x, int y = rng()) {
        int l, r; split(root, x, l, r);
        root = merge(merge(l, make(x, y)), r);
    }

    void erase(int x) {
        int l, m, r; split(root, x - 1, l, r), split(r, x, m, r);
        m = merge(tree[m].l, tree[m].r);
        root = merge(merge(l, m), r);
    }

    int index(int x) {
        int i = root, k = 0;
        while (i != 0) {
            if (tree[i].x < x) k += 1 + tree[tree[i].l].s, i = tree[i].r;
            else i = tree[i].l;
        }
        return k;
    }

    int kth(int k) {
        int i = root;
        while (i != 0) {
            int s = tree[tree[i].l].s;
            if (k < s) i = tree[i].l;
            else if (k > s) k -= 1 + s, i = tree[i].r;
            else return tree[i].x;
        }
        return -1;
    }

    int unite(int i, int j) {
        if (i == 0 or j == 0) return i | j;
        if (tree[i].y < tree[j].y) swap(i, j);
        int l, r; split(j, tree[i].x, l, r);
        tree[i].l = unite(tree[i].l, l);
        tree[i].r = unite(tree[i].r, r);
        return update(i), i;
    }
};
