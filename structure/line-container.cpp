struct line {
    int a, b;
    mutable int end;

    bool operator<(const line &other) const {
        return tie(a, b) < tie(other.a, other.b);
    }

    bool operator<(const int x) const {
        return end < x;
    }
};

struct line_container : multiset<line, less<>> {
    int intersect(iterator i, iterator j) {
        int x = j->b - i->b, y = i->a - j->a;
        return x / y - ((x ^ y) < 0 and x % y != 0);
    }

    void update(iterator i) {
        if (next(i) == end()) {
            i->end = inf;
        } else {
            i->end = intersect(i, next(i));
        }
    }

    void include(int a, int b) {
        iterator l = insert({a, b, 0});

        if (l != begin() and prev(l)->a == l->a) {
            erase(prev(l));
        }
        if (next(l) != end() and next(l)->a == l->a) {
            erase(l);
            return;
        }

        if (l != begin() and next(l) != end()) {
            iterator p = prev(l), n = next(l);
            if (intersect(p, l) >= intersect(l, n)) {
                erase(l);
                return;
            }
        }

        while (l != begin()) {
            iterator p = prev(l);
            if (p != begin() and intersect(prev(p), p) >= intersect(p, l)) {
                erase(p);
                continue;
            }
            break;
        }

        while (next(l) != end()) {
            iterator n = next(l);
            if (next(n) != end() and intersect(l, n) >= intersect(n, next(n))) {
                erase(n);
                continue;
            }
            break;
        }

        if (l != begin()) update(prev(l));
        update(l);
    }

    int max(int x) {
        auto l = lower_bound(x);
        return l->a * x + l->b;
    }
};
