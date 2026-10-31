// Line Container: dynamic convex hull trick for maximum
// Time: insert/query O(log N) | Space: O(N)
// Note: computes max(ax + b) | change '<' to '>' in line operator for min
struct line {
    mutable int a, b, last;

    bool operator<(const line &o) const {
        return tie(a, b) < tie(o.a, o.b);
    }

    bool operator<(int x) const {
        return last < x;
    }
};

struct line_container : multiset<line, less<>> {
    int floor(int n, int d) {
        return n / d - ((n ^ d) < 0 and n % d != 0);
    }

    bool intersect(iterator s, iterator t) {
        if (t == end()) return s->last = inf, false;
        if (s->a == t->a) s->last = -inf;
        else s->last = floor(t->b - s->b, s->a - t->a);
        return s->last >= t->last;
    }

    void insert(int a, int b) {
        auto curr = multiset::insert({a, b, 0}), after = next(curr), before = curr;
        while (intersect(curr, after)) after = erase(after);
        if (before != begin() and intersect(--before, curr)) intersect(before, curr = erase(curr));
        while ((curr = before) != begin() and (--before)->last >= curr->last) intersect(before, erase(curr));
    }

    int query(int x) {
        auto l = lower_bound(x);
        return l->a * x + l->b;
    }
};
