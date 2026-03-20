// Implicit Treap: Dynamic Array with Range Updates and Queries
// Time: Operations O(log N) average | Space: O(N)
// Note: Supports Range Modifications | Uses Lazy Propagation and Implicit Indices
struct implicit_treap {
    struct node {
        int v, p, s, l, r;
        int data, lazy;
    };

    int root = 0;
    vector<node> t = {{}};

    int make(int v, int p = rng()) {
        t.push_back({v, p, 1, 0, 0, v, 0});
        return t.size() - 1;
    }

    void apply(int i, int v) {
        if (i == 0) return;
        t[i].v += v;
        t[i].data += v * t[i].s;
        t[i].lazy += v;
    }

    void push(int i) {
        if (t[i].lazy == 0) return;
        apply(t[i].l, t[i].lazy);
        apply(t[i].r, t[i].lazy);
        t[i].lazy = 0;
    }

    void pull(int i) {
        if (i == 0) return;
        t[i].s = t[t[i].l].s + 1 + t[t[i].r].s;
        t[i].data = t[t[i].l].data + t[i].v + t[t[i].r].data;
    }

    pair<int, int> split(int i, int k) {
        if (i == 0) return {0, 0};
        push(i);
        int s = t[t[i].l].s;
        if (s >= k) {
            auto [l, r] = split(t[i].l, k);
            t[i].l = r;
            pull(i);
            return {l, i};
        } else {
            auto [l, r] = split(t[i].r, k - s - 1);
            t[i].r = l;
            pull(i);
            return {i, r};
        }
    }

    int merge(int l, int r) {
        if (l == 0 or r == 0) return l | r;
        if (t[l].p > t[r].p) {
            push(l);
            t[l].r = merge(t[l].r, r);
            pull(l);
            return l;
        } else {
            push(r);
            t[r].l = merge(l, t[r].l);
            pull(r);
            return r;
        }
    }

    void insert(int k, int v) {
        auto [l, r] = split(root, k);
        root = merge(merge(l, make(v)), r);
    }

    void erase(int k) {
        auto [l, m] = split(root, k);
        auto [_, r] = split(m, 1);
        root = merge(l, r);
    }

    void update(int i, int j, int v) {
        auto [h, r] = split(root, j + 1);
        auto [l, m] = split(h, i);
        apply(m, v);
        root = merge(merge(l, m), r);
    }

    int query(int i, int j) {
        auto [h, r] = split(root, j + 1);
        auto [l, m] = split(h, i);
        int q = t[m].data;
        root = merge(merge(l, m), r);
        return q;
    }
};
