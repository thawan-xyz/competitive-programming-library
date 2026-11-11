bool on_ray(point a, point b, point p) {
    if (a == b) return p == a;
    return sign(orient(a, b, p)) == 0 and sign(dot(b - a, p - a)) >= 0;
}

float ray_point(point a, point b, point p) {
    if (a != b and dot(b - a, p - a) > 0) return line(a, b).dist(p);
    return sqrt(dist2(p, a));
}

float ray_ray(point a, point b, point c, point d) {
    if (a == b) return ray_point(c, d, a);
    if (c == d) return ray_point(a, b, c);
    point v = b - a, w = d - c;
    int s = sign(cross(v, w));
    if (s != 0 and sign(cross(c - a, w)) * s >= 0 and sign(cross(c - a, v)) * s >= 0) return 0;
    return min(ray_point(a, b, c), ray_point(c, d, a));
}
