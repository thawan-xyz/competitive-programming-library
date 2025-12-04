struct point {
    float x, y;

    point operator-(point &other) {
        return {x - other.x, y - other.y};
    }
};

int orient(point &a, point &b, point &p) {
    point v = b - a;
    point w = p - a;

    float cross = v.x * w.y - v.y * w.x;
    if (cross > 0) return -1;
    if (cross < 0) return +1;
    return 0;
}

bool between(point &a, point &b, point &p) {
    if (orient(a, b, p) != 0) return false;

    bool x = min(a.x, b.x) <= p.x and p.x <= max(a.x, b.x);
    bool y = min(a.y, b.y) <= p.y and p.y <= max(a.y, b.y)
    return x and y;
}

point project(point &a, point &b, point &p) {
    point v = b - a;
    point w = p - a;

    float t = (v.x * w.x + v.y * w.y) / (v.x * v.x + v.y * v.y);
    return {a.x + t * v.x, a.y + t * v.y};
}
