float ray_point(point a, point b, point p) {
    if (a != b) {
        line l(a, b);
        if (l.comp(a, p)) return l.dist(p);
    }
    return dist(p, a);
}

float ray_ray(point a, point b, point c, point d) {
    if (a == b) return ray_point(c, d, a);
    if (c == d) return ray_point(a, b, c);
    line l(a, b), r(c, d);
    if (cross(l.v, r.v) != 0) {
        point p = inter(l, r);
        if (l.comp(a, p) and r.comp(c, p)) return 0;
    }
    return min(ray_point(a, b, c), ray_point(c, d, a));
}
