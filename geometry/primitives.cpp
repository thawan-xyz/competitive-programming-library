struct point {
    float x, y;

    bool operator==(const point &other) const {
        return x == other.x and y == other.y;
    }

    bool operator<(const point &other) const {
        return tie(x, y) < tie(other.x, other.y);
    }

    point operator-(const point &other) const {
        return {x - other.x, y - other.y};
    }

    static float dist(point &a, point &b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return sqrt(dx * dx + dy * dy);
    }

    static float dot(point &a, point &b) {
        return a.x * b.x + a.y * b.y;
    }
};

struct line {
    point a, b;

    int orientation(point &p) {
        point v = b - a;
        point w = p - a;

        float c = v.x * w.y - v.y * w.x;
        if (c > 0) return -1;
        if (c < 0) return +1;
        return 0;
    }

    bool between(point &p) {
        if (orientation(p) != 0) return false;

        bool bx = min(a.x, b.x) <= p.x and p.x <= max(a.x, b.x);
        bool by = min(a.y, b.y) <= p.y and p.y <= max(a.y, b.y);
        return bx and by;
    }

    point project(point &p) {
        point v = b - a;
        point w = p - a;

        float t = point::dot(v, w) / point::dot(v, v);
        if (t < 0) t = 0;
        if (t > 1) t = 1;

        return {a.x + t * v.x, a.y + t * v.y};
    }

    float dist(point &p) {
        point q = project(p);
        return point::dist(p, q);
    }

    line normal() {
        point v = b - a;
        v = {-v.y, v.x};

        point c = {(a.x + b.x) / 2, (a.y + b.y) / 2};
        point d = {c.x + v.x, c.y + v.y};
        return {c, d};
    }

    static float angle(line &s, line &t) {
        point v = s.b - s.a;
        point w = t.b - t.a;

        float c = point::dot(v, w) / sqrt(point::dot(v, v) * point::dot(w, w));
        if (c < -1) c = -1;
        if (c > 1) c = 1;

        return acos(c);
    }

    static bool intersect(line &s, line &t) {
        if (s.between(t.a) or s.between(t.b)) return true;
        if (t.between(s.a) or t.between(s.b)) return true;

        if (s.orientation(t.a) == s.orientation(t.b)) return false;
        if (t.orientation(s.a) == t.orientation(s.b)) return false;

        return true;
    }

    static float dist(line &s, line &t) {
        if (line::intersect(s, t)) return 0;
        return min({s.dist(t.a), s.dist(t.b), t.dist(s.a), t.dist(s.b)});
    }
};
