bool in_disk(point a, point b, point p) {
    return dot(a - p, b - p) <= 0;
}

bool on_segment(point a, point b, point p) {
    return orient(a, b, p) == 0 and in_disk(a, b, p);
}

vector<point> proper_inter(point a, point b, point c, point d) {
    T oa = orient(c, d, a),
      ob = orient(c, d, b),
      oc = orient(a, b, c),
      od = orient(a, b, d);
    if (sign(oa) * sign(ob) >= 0 or sign(oc) * sign(od) >= 0) return {};
    return {(a * ob - b * oa) / (ob - oa)};
}

vector<point> inters(point a, point b, point c, point d) {
    vector<point> p = proper_inter(a, b, c, d);
    if (p.size()) return p;
    if (on_segment(c, d, a)) p.push_back(a);
    if (on_segment(c, d, b)) p.push_back(b);
    if (on_segment(a, b, c)) p.push_back(c);
    if (on_segment(a, b, d)) p.push_back(d);
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    return p;
}

float segment_point(point a, point b, point p) {
    if (a != b) {
        line l(a, b);
        if (l.comp(a, p) and l.comp(p, b)) return l.dist(p);
    }
    return min(dist(p, a), dist(p, b));
}

float segment_segment(point a, point b, point c, point d) {
    if (proper_inter(a, b, c, d).size()) return 0;
    return min({segment_point(a, b, c), segment_point(a, b, d),
                segment_point(c, d, a), segment_point(c, d, b)});
}
