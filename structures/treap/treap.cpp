// Treap: randomized binary search tree (split/merge)
// Time: operations O(log N) average | Space: O(N)
// Note: combines bst and heap properties | requires mt19937 for priorities
struct treap {
    struct node {
        int x, p, l = 0, r = 0, s = 1;

        node(int x, int p = rng()): x(x), p(p) {}
    };

    int root = 0;
    vector<node> t;

    treap(int n = 0) {
        t.reserve(n + 1);
        t.push_back(node(0));
        t[0].s = 0;
    }

    void pull(int i) {
        if (i == 0) return;
        t[i].s = 1 + t[t[i].l].s + t[t[i].r].s;
    }

    pair<int, int> split(int i, int x) {
        if (i == 0) return {0, 0};
        if (t[i].x <= x) {
            auto [l, r] = split(t[i].r, x);
            t[i].r = l;
            pull(i);
            return {i, r};
        } else {
            auto [l, r] = split(t[i].l, x);
            t[i].l = r;
            pull(i);
            return {l, i};
        }
    }

    int merge(int l, int r) {
        if (l == 0 or r == 0) return l | r;
        if (t[l].p > t[r].p) {
            t[l].r = merge(t[l].r, r);
            pull(l);
            return l;
        } else {
            t[r].l = merge(l, t[r].l);
            pull(r);
            return r;
        }
    }

    void insert(int x) {
        auto [l, r] = split(root, x);
        int i = t.size();
        t.push_back(node(x));
        root = merge(merge(l, i), r);
    }

    void erase(int x) {
        auto [l, h] = split(root, x - 1);
        auto [m, r] = split(h, x);
        m = merge(t[m].l, t[m].r);
        root = merge(merge(l, m), r);
    }

    int index(int x) {
        int i = root, k = 0;
        while (i != 0) {
            if (t[i].x < x) k += 1 + t[t[i].l].s, i = t[i].r;
            else i = t[i].l;
        }
        return k;
    }

    int kth(int k) {
        int i = root;
        while (i != 0) {
            int s = t[t[i].l].s;
            if (k < s) i = t[i].l;
            else if (k > s) k -= 1 + s, i = t[i].r;
            else return t[i].x;
        }
        return -1;
    }
};
