struct sparse_segment_tree {
    struct tag {
        int x = 0;

        bool operator==(const tag &o) const {
            return x == o.x;
        }
    };

    struct node {
        int sum = 0;
        tag lazy;
        int l = 0, r = 0;

        node operator+(const node &o) const {
            node c;
            c.sum = sum + o.sum;
            return c;
        }

        void apply(const tag &t, int len) {
            sum += t.x * len;
            lazy.x += t.x;
        }

        bool good(int x) const {
            return sum >= x;
        }
    };

    int low, high, root = 0;
    bool keep;
    vector<node> tree = {node()};

    sparse_segment_tree(int low, int high, bool keep): low(low), high(high), keep(keep) {}

    int touch(int p) {
        if (p and not keep) return p;
        tree.push_back(tree[p]);
        return tree.size() - 1;
    }

    void push(int p, int l, int r) {
        if (tree[p].lazy == tree[0].lazy) return;
        int m = l + (r - l) / 2;
        tree[p].l = touch(tree[p].l), tree[p].r = touch(tree[p].r);
        tag t = tree[p].lazy;
        tree[tree[p].l].apply(t, m - l + 1);
        tree[tree[p].r].apply(t, r - m);
        tree[p].lazy = tree[0].lazy;
    }

    void pull(int p) {
        node c = tree[tree[p].l] + tree[tree[p].r];
        c.l = tree[p].l, c.r = tree[p].r;
        tree[p] = c;
    }

    int set(int i, const node &x, int v = -1) {
        auto rec = [&](auto &self, int p, int l, int r) -> int {
            p = touch(p);
            if (l == r) return tree[p] = x, p;
            push(p, l, r);
            int m = l + (r - l) / 2;
            if (i <= m) tree[p].l = self(self, tree[p].l, l, m);
            else tree[p].r = self(self, tree[p].r, m + 1, r);
            pull(p);
            return p;
        };
        return root = rec(rec, v < 0 ? root : v, low, high);
    }

    int update(int ql, int qr, const tag &t, int v = -1) {
        auto rec = [&](auto &self, int p, int l, int r) -> int {
            if (qr < l or r < ql) return p;
            p = touch(p);
            if (ql <= l and r <= qr) return tree[p].apply(t, r - l + 1), p;
            push(p, l, r);
            int m = l + (r - l) / 2;
            tree[p].l = self(self, tree[p].l, l, m);
            tree[p].r = self(self, tree[p].r, m + 1, r);
            pull(p);
            return p;
        };
        return root = rec(rec, v < 0 ? root : v, low, high);
    }

    node query(int ql, int qr, int v = -1) {
        auto rec = [&](auto &self, int p, int l, int r) -> node {
            if (qr < l or r < ql) return node();
            if (not p or (ql <= l and r <= qr)) return tree[p];
            push(p, l, r);
            int m = l + (r - l) / 2;
            return self(self, tree[p].l, l, m) + self(self, tree[p].r, m + 1, r);
        };
        return rec(rec, v < 0 ? root : v, low, high);
    }

    int left(int qr, int x, int v = -1) {
        node acc;
        auto rec = [&](auto &self, int p, int l, int r) -> int {
            if (qr < l) return l - 1;
            node c = tree[p] + acc;
            if (r <= qr and not c.good(x)) return acc = c, l - 1;
            if (l == r) return l;
            push(p, l, r);
            int m = l + (r - l) / 2, i = self(self, tree[p].r, m + 1, r);
            return i > m ? i : self(self, tree[p].l, l, m);
        };
        return rec(rec, v < 0 ? root : v, low, high);
    }

    int right(int ql, int x, int v = -1) {
        node acc;
        auto rec = [&](auto &self, int p, int l, int r) -> int {
            if (r < ql) return r + 1;
            node c = acc + tree[p];
            if (ql <= l and not c.good(x)) return acc = c, r + 1;
            if (l == r) return l;
            push(p, l, r);
            int m = l + (r - l) / 2, i = self(self, tree[p].l, l, m);
            return i <= m ? i : self(self, tree[p].r, m + 1, r);
        };
        return rec(rec, v < 0 ? root : v, low, high);
    }
};
