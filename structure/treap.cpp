struct treap {
private:
    struct node {
        int k, p, l, r, s;

        node(int k = 0, int p = 0): k(k), p(p), l(0), r(0), s(1) {}
    };

    int make(int k, int p) {
        int i = t.size();
        t.push_back(node(k, p));
        return i;
    }

    int size(int i) {
        return i ? t[i].s : 0;
    }

    void update(int i) {
        t[i].s = 1 + size(t[i].l) + size(t[i].r);
    }

    pair<int, int> split(int i, int k) {
        if (not i) return {0, 0};

        if (t[i].k <= k) {
            auto [l, r] = split(t[i].r, k);
            t[i].r = l;
            update(i);
            return {i, r};
        } else {
            auto [l, r] = split(t[i].l, k);
            t[i].l = r;
            update(i);
            return {l, i};
        }
    }

    int merge(int l, int r) {
        if (not l) return r;
        if (not r) return l;

        if (t[l].p > t[r].p) {
            t[l].r = merge(t[l].r, r);
            update(l);
            return l;
        } else {
            t[r].l = merge(l, t[r].l);
            update(r);
            return r;
        }
    }

    int insert(int i, int k, int p) {
        if (not i) return make(k, p);

        if (t[i].p < p) {
            auto [l, r] = split(i, k);
            i = make(k, p);
            t[i].l = l;
            t[i].r = r;
        } else {
            if (k <= t[i].k) t[i].l = insert(t[i].l, k, p);
            if (k > t[i].k) t[i].r = insert(t[i].r, k, p);
        }
        update(i);
        return i;
    }

    int erase(int i, int k) {
        if (not i) return 0;

        if (k == t[i].k) return merge(t[i].l, t[i].r);
        if (k < t[i].k) t[i].l = erase(t[i].l, k);
        if (k > t[i].k) t[i].r = erase(t[i].r, k);
        update(i);
        return i;
    }

    int index(int i, int k) {
        if (not i) return -1;

        if (k == t[i].k) return size(t[i].l);
        if (k < t[i].k) return index(t[i].l, k);

        int r = index(t[i].r, k);
        if (r == -1) return -1;
        return 1 + size(t[i].l) + r;
    }

    int kth(int i, int k) {
        if (not i) return -1;

        int l = size(t[i].l);
        if (k == l) return t[i].k;

        if (k < l) return kth(t[i].l, k);
        return kth(t[i].r, k - (l + 1));
    }

public:
    array<node> t;
    int root;

    treap(): t(1), root(0) {}

    void insert(int k) {
        int p = random;
        root = insert(root, k, p);
    }

    void erase(int k) {
        root = erase(root, k);
    }

    int index(int k) {
        return index(root, k);
    }

    int operator[](int i) {
        return kth(root, i);
    }

    int unite(int i, int j) {
        if (not i) return j;
        if (not j) return i;

        if (t[i].p < t[j].p) swap(i, j);
        auto [l, r] = split(j, t[i].k);

        t[i].l = unite(t[i].l, l);
        t[i].r = unite(t[i].r, r);
        return i;
    }
};
