point incircle(point a, point b, point c) {
    T ab = dist(a, b);
    T bc = dist(b, c);
    T ac = dist(a, c);
    T p = ab + bc + ac;
    if (p == 0) return {};
    return (a * bc + b * ac + c * ab) / p;
}

point circumcircle(point a, point b, point c) {
    point v = b - a;
    point w = c - a;
    T h = cross(v, w);
    if (h == 0) return {};
    return a + perp(v * norm(w) - w * norm(v)) / (2.0 * h);
}

vector<point> circle_line_inter(point o, T r, line l) {
    T s = l.side(o);
    T d2 = (s * s) / norm(l.v);
    T h2 = r * r - d2;
    if (h2 < 0) return {};
    point p = l.proj(o);
    if (h2 == 0) return {p};
    point h = l.v * sqrt(h2 / norm(l.v));
    return {p - h, p + h};
}

vector<point> circle_segment_inter(point o, T r, point a, point b) {
    if (a == b) {
        if (norm(a - o) == r * r) return {a};
        return {};
    }
    vector<point> l = circle_line_inter(o, r, line(a, b));
    vector<point> h;
    for (point p : l) if (in_disk(a, b, p)) h.push_back(p);
    return h;
}

T circle_inter_area(point o1, T r1, point o2, T r2) {
    T d = dist(o1, o2);
    if (d >= r1 + r2) return 0.0;
    if (d <= abs(r1 - r2)) return pi * min(r1, r2) * min(r1, r2);
    T h1 = 2.0 * acos((d * d + r1 * r1 - r2 * r2) / (2.0 * d * r1));
    T h2 = 2.0 * acos((d * d + r2 * r2 - r1 * r1) / (2.0 * d * r2));
    T a1 = 0.5 * r1 * r1 * (h1 - sin(h1));
    T a2 = 0.5 * r2 * r2 * (h2 - sin(h2));
    return a1 + a2;
}

vector<point> circle_inter(point o1, T r1, point o2, T r2) {
    point v = o2 - o1;
    T d2 = norm(v);
    if (d2 == 0) return {};
    T op = (d2 + r1 * r1 - r2 * r2) / 2.0;
    T h2 = r1 * r1 - (op * op) / d2;
    if (h2 < 0) return {};
    point p = o1 + v * (op / d2);
    if (h2 == 0) return {p};
    point h = perp(v) * sqrt(h2 / d2);
    return {p - h, p + h};
}
