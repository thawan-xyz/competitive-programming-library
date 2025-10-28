struct line {
    int a, b;
    mutable float end;

    bool operator<(const line &other) const {
        return a > other.a;
    }

    bool operator<(const float x) const {
        return end < x;
    }
};

struct line_container : multiset<line, less<>> {
    float intersect(iterator i, iterator j) {
        float x = j->b - i->b, y = i->a - j->a;
        return x / y;
    }

    void update(iterator i) {
        if (next(i) == end()) {
            i->end = inf;
        } else {
            i->end = intersect(i, next(i));
        }
    }

    void insert_line(int a, int b) {
        auto y = insert({a, b, 0});
        auto x = (y == begin()) ? end() : prev(y);
        auto z = next(y);

        if (x != end() and x->a == y->a) {
            if (x->b > y->b) {
                erase(x);
            } else {
                erase(y);
                return;
            }
        }

        if (z != end() and y->a == z->a) {
            if (y->b < z->b) {
                erase(z);
            } else {
                erase(y);
                return;
            }
        }

        while (true) {
            if (y == begin()) break;
            auto p1 = prev(y);
            if (p1 == begin()) break;
            auto p2 = prev(p1);
            if (intersect(p2, p1) >= intersect(p1, y)) {
                erase(p1);
                continue;
            }
            break;
        }

        while (true) {
            auto n1 = next(y);
            if (n1 == end()) break;
            auto n2 = next(n1);
            if (n2 != end() && intersect(y, n1) >= intersect(n1, n2)) {
                erase(n1);
                continue;
            }
            if (y != begin()) {
                auto p = prev(y);
                if (intersect(p, y) >= intersect(y, n1)) {
                    erase(y);
                    y = p;
                    continue;
                }
            }
            break;
        }

        if (y != begin()) update(prev(y));
        update(y);
    }

    int query(int x) {
        auto l = lower_bound(x);
        return l->a * x + l->b;
    }
};
