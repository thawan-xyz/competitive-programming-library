bool in_disk(point a, point b, point p) {
    return sign(dot(a - p, b - p)) <= 0;
}

bool on_segment(point a, point b, point p) {
    return sign(orient(a, b, p)) == 0 and in_disk(a, b, p);
}

bool proper(point a, point b, point c, point d) {
    return sign(orient(c, d, a)) * sign(orient(c, d, b)) < 0 and sign(orient(a, b, c)) * sign(orient(a, b, d)) < 0;
}

bool intersects(point a, point b, point c, point d) {
    return proper(a, b, c, d) or on_segment(c, d, a) or on_segment(c, d, b) or on_segment(a, b, c) or on_segment(a, b, d);
}

vector<point> proper_inter(point a, point b, point c, point d) {
    assert(is_floating_point_v<T>);
    if (not proper(a, b, c, d)) return {};
    T oa = orient(c, d, a), ob = orient(c, d, b);
    return {(a * ob - b * oa) / (ob - oa)};
}

vector<point> inters(point a, point b, point c, point d) {
    assert(is_floating_point_v<T>);
    if (proper(a, b, c, d)) return proper_inter(a, b, c, d);
    vector<point> p;
    for (point q : {a, b}) if (on_segment(c, d, q)) p.push_back(q);
    for (point q : {c, d}) if (on_segment(a, b, q)) p.push_back(q);
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    return p;
}

float segment_point(point a, point b, point p) {
    if (a != b and dot(b - a, p - a) > 0 and dot(a - b, p - b) > 0) return line(a, b).dist(p);
    return sqrt(min(dist2(p, a), dist2(p, b)));
}

float segment_segment(point a, point b, point c, point d) {
    if (proper(a, b, c, d)) return 0;
    return min({segment_point(a, b, c), segment_point(a, b, d), segment_point(c, d, a), segment_point(c, d, b)});
}

float segment_ray(point a, point b, point c, point d) {
    if (c == d) return segment_point(a, b, c);
    point v = d - c, w = b - a;
    int s = sign(cross(v, w));
    if (s != 0 and sign(cross(a - c, w)) * s >= 0 and sign(cross(a - c, v)) * s >= 0 and sign(cross(a - c, v) - cross(v, w)) * s <= 0) return 0;
    return min({ray_point(c, d, a), ray_point(c, d, b), segment_point(a, b, c)});
}
