struct line {
    int a, b;
    mutable int i;

    bool operator<(const line &other) const {
        return tie(a, b) < tie(other.a, other.b);
    }

    bool operator<(const int x) const {
        return i < x;
    }
};

struct line_container : multiset<line, less<>> {
private:
    int intersect(iterator s, iterator t) {
        int x = t->b - s->b, y = s->a - t->a;
        return x / y - ((x ^ y) < 0 and x % y != 0);
    }

    void update(iterator s) {
        if (next(s) == end()) {
            s->i = inf;
        } else {
            s->i = intersect(s, next(s));
        }
    }

public:
    void insert(int a, int b) {
        iterator l = multiset::insert({a, b, 0});

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

        if (l != begin()) {
            update(prev(l));
        }
        update(l);
    }

    int query(int x) {
        auto l = lower_bound(x);
        return l->a * x + l->b;
    }
};
