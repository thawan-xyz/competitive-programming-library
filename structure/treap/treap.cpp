// Treap: Randomized Binary Search Tree (Split/Merge)
// Time: Operations O(log N) average | Space: O(N)
// Note: Combines BST and Heap Properties | Requires mt19937 for Priorities
struct treap {
    struct node {
        int v, p, l, r, s;
    };

    int root = 0;
    vector<node> t = {{}};

    int make(int v, int p = rng()) {
        t.push_back({v, p, 0, 0, 1});
        return t.size() - 1;
    }

    void pull(int i) {
        t[i].s = 1 + t[t[i].l].s + t[t[i].r].s;
    }

    pair<int, int> split(int i, int v) {
        if (i == 0) return {0, 0};
        if (t[i].v <= v) {
            auto [l, r] = split(t[i].r, v);
            t[i].r = l;
            pull(i);
            return {i, r};
        } else {
            auto [l, r] = split(t[i].l, v);
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

    void insert(int v) {
        auto [l, r] = split(root, v);
        root = merge(merge(l, make(v)), r);
    }

    void erase(int v) {
        auto [l, h] = split(root, v - 1);
        auto [m, r] = split(h, v);
        m = merge(t[m].l, t[m].r);
        root = merge(merge(l, m), r);
    }

    int index(int v) {
        int i = root, k = 0;
        while (i != 0) {
            if (t[i].v < v) k += 1 + t[t[i].l].s, i = t[i].r;
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
            else return t[i].v;
        }
        return -1;
    }
};
