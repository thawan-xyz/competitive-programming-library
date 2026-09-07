// In Disk: checks if point p lies inside or on the circle with diameter ab
// Note: true if the angle at p is >= 90 degrees (dot product <= 0)
bool in_disk(point a, point b, point p) {
    return dot(a - p, b - p) <= 0;
}

// On Segment: determines if point p lies strictly on the line segment ab
// Note: true if p is colinear to ab and lies within the bounding disk of ab
bool on_segment(point a, point b, point p) {
    return orient(a, b, p) == 0 and in_disk(a, b, p);
}

// Proper Intersection: finds the strict interior intersection of segments ab and cd
// Note: returns true and the exact float point if they cross
pair<bool, complex<float>> proper_inter(point a, point b, point c, point d) {
    float oa = cross(d - c, a - c),
          ob = cross(d - c, b - c),
          oc = cross(b - a, c - a),
          od = cross(b - a, d - a);
    if (oa * ob < 0 and oc * od < 0) {
        return {true, (complex<float>(a) * ob - complex<float>(b) * oa) / (ob - oa)};
    }
    return {false, {}};
}

// Segment Intersection: finds all intersection points or overlapping segment endpoints
// Note: handles strict crossings, touching endpoints, and collinear overlaps
vector<complex<float>> inters(point a, point b, point c, point d) {
    auto [f, p] = proper_inter(a, b, c, d);
    if (f) return {p};
    vector<complex<float>> ps;
    if (on_segment(c, d, a)) ps.push_back(complex<float>(a));
    if (on_segment(c, d, b)) ps.push_back(complex<float>(b));
    if (on_segment(a, b, c)) ps.push_back(complex<float>(c));
    if (on_segment(a, b, d)) ps.push_back(complex<float>(d));
    sort(ps.begin(), ps.end(), [&](complex<float> p1, complex<float> p2) {
        return pair(p1.x, p1.y) < pair(p2.x, p2.y);
    });
    ps.erase(unique(ps.begin(), ps.end()), ps.end());
    return ps;
}

// Point-Segment Distance: finds the shortest distance from point p to segment ab
// Note: uses orthogonal distance if p projects strictly inside ab, otherwise checks endpoints
float segment_point(point a, point b, point p) {
    if (a != b) {
        line l(a, b);
        if (l.comp(a, p) and l.comp(p, b)) return l.dist(p);
    }
    return min(dist(p, a), dist(p, b));
}

// Segment-Segment Distance: finds the shortest distance between segments ab and cd
// Note: returns 0 if they cross, otherwise checks all endpoint-to-segment pairs
float segment_segment(point a, point b, point c, point d) {
    if (proper_inter(a, b, c, d).first) return 0;
    return min({segment_point(a, b, c), segment_point(a, b, d),
                segment_point(c, d, a), segment_point(c, d, b)});
}
