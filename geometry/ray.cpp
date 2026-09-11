// Ray-Point Distance: finds the shortest distance from ray ab to point p
// Note: uses orthogonal distance if p projects strictly in front of origin a, otherwise returns distance to a
float ray_point(point a, point b, point p) {
    if (a != b) {
        line l(a, b);
        if (l.comp(a, p)) return l.dist(p);
    }
    return dist(p, a);
}

// Ray-Ray Distance: finds the shortest distance between rays ab and cd
// Note: returns 0 if they intersect in the forward direction, otherwise checks origin-to-ray pairs
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
