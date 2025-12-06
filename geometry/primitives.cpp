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

    int orient(point &p) {
        point v = b - a;
        point w = p - a;

        float c = v.x * w.y - v.y * w.x;
        if (c > 0) return -1;
        if (c < 0) return +1;
        return 0;
    }

    bool between(point &p) {
        if (orient(p) != 0) return false;

        bool x = min(a.x, b.x) <= p.x and p.x <= max(a.x, b.x);
        bool y = min(a.y, b.y) <= p.y and p.y <= max(a.y, b.y);
        return x and y;
    }

    point project(point &p) {
        point v = b - a;
        point w = p - a;

        float t = point::dot(v, w) / point::dot(v, v);
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
};
