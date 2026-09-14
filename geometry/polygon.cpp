float triangle_area(point a, point b, point c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

float polygon_area(const vector<point> &p) {
    T area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) area += cross(p[i], p[(i + 1) % n]);
    return abs(area) / 2.0;
}

bool equal_above(point p, point a) {
    return p.y >= a.y;
}

bool crosses_ray(point p, point q, point a) {
    return (equal_above(q, a) - equal_above(p, a)) * orient(a, p, q) > 0;
}

bool cutting_ray_test(const vector<point> &p, point a, bool strict) {
    int c = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) {
        if (on_segment(p[i], p[(i + 1) % n], a)) return not strict;
        c += crosses_ray(p[i], p[(i + 1) % n], a);
    }
    return c & 1;
}
