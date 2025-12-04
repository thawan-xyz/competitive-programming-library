struct point {
    float x, y;

    point operator-(point &other) {
        return {x - other.x, y - other.y};
    }
};

point project(point &a, point &b, point &p) {
    point v = b - a;
    point w = p - a;

    float t = (v.x * w.x + v.y * w.y) / (v.x * v.x + v.y * v.y);
    return {a.x + t * v.x, a.y + t * v.y};
}
