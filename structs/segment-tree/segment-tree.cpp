struct segment_tree {
    struct tag {
        int x = 0;

        bool operator==(const tag &o) const {
            return x == o.x;
        }
    };

    struct node {
        int sum = 0;
        tag lazy;

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

    int n;
    vector<node> tree;

    segment_tree(int n): n(n), tree(4 * n) {}

    void push(int p, int l, int r) {
        if (tree[p].lazy == tag()) return;
        int m = l + (r - l) / 2;
        tree[2 * p].apply(tree[p].lazy, m - l + 1);
        tree[2 * p + 1].apply(tree[p].lazy, r - m);
        tree[p].lazy = tag();
    }

    void pull(int p) {
        tree[p] = tree[2 * p] + tree[2 * p + 1];
    }

    void build(const vector<node> &a) {
        auto rec = [&](auto &self, int p, int l, int r) -> void {
            if (l == r) {
                tree[p] = a[l];
                return;
            }
            int m = l + (r - l) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m + 1, r);
            pull(p);
        };
        rec(rec, 1, 0, n - 1);
    }

    void set(int i, const node &x) {
        auto rec = [&](auto &self, int p, int l, int r) -> void {
            if (l == r) {
                tree[p] = x;
                return;
            }
            push(p, l, r);
            int m = l + (r - l) / 2;
            if (i <= m) self(self, 2 * p, l, m);
            else self(self, 2 * p + 1, m + 1, r);
            pull(p);
        };
        rec(rec, 1, 0, n - 1);
    }

    void update(int ql, int qr, const tag &t) {
        auto rec = [&](auto &self, int p, int l, int r) -> void {
            if (qr < l or r < ql) return;
            if (ql <= l and r <= qr) return tree[p].apply(t, r - l + 1);
            push(p, l, r);
            int m = l + (r - l) / 2;
            self(self, 2 * p, l, m);
            self(self, 2 * p + 1, m + 1, r);
            pull(p);
        };
        rec(rec, 1, 0, n - 1);
    }

    node query(int ql, int qr) {
        auto rec = [&](auto &self, int p, int l, int r) -> node {
            if (qr < l or r < ql) return node();
            if (ql <= l and r <= qr) return tree[p];
            push(p, l, r);
            int m = l + (r - l) / 2;
            return self(self, 2 * p, l, m) + self(self, 2 * p + 1, m + 1, r);
        };
        return rec(rec, 1, 0, n - 1);
    }

    int left(int qr, int x) {
        node acc;
        auto rec = [&](auto &self, int p, int l, int r) -> int {
            if (qr < l) return l - 1;
            node c = tree[p] + acc;
            if (r <= qr and not c.good(x)) return acc = c, l - 1;
            if (l == r) return l;
            push(p, l, r);
            int m = l + (r - l) / 2, i = self(self, 2 * p + 1, m + 1, r);
            return i > m ? i : self(self, 2 * p, l, m);
        };
        return rec(rec, 1, 0, n - 1);
    }

    int right(int ql, int x) {
        node acc;
        auto rec = [&](auto &self, int p, int l, int r) -> int {
            if (r < ql) return r + 1;
            node c = acc + tree[p];
            if (ql <= l and not c.good(x)) return acc = c, r + 1;
            if (l == r) return l;
            push(p, l, r);
            int m = l + (r - l) / 2, i = self(self, 2 * p, l, m);
            return i <= m ? i : self(self, 2 * p + 1, m + 1, r);
        };
        return rec(rec, 1, 0, n - 1);
    }
};
