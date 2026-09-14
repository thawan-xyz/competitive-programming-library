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
// Note: returns a single-element vector if they strictly cross, or empty otherwise
vector<point> proper_inter(point a, point b, point c, point d) {
    T oa = orient(c, d, a),
      ob = orient(c, d, b),
      oc = orient(a, b, c),
      od = orient(a, b, d);
    if (sign(oa) * sign(ob) >= 0 or sign(oc) * sign(od) >= 0) return {};
    return {(a * ob - b * oa) / (ob - oa)};
}

// Segment Intersection: finds all intersection points or overlapping segment endpoints
// Note: handles strict crossings, touching endpoints, and collinear overlap
vector<point> inters(point a, point b, point c, point d) {
    vector<point> p = proper_inter(a, b, c, d);
    if (p.size()) return p;
    if (on_segment(c, d, a)) p.push_back(a);
    if (on_segment(c, d, b)) p.push_back(b);
    if (on_segment(a, b, c)) p.push_back(c);
    if (on_segment(a, b, d)) p.push_back(d);
    sort(p.begin(), p.end(), [&](point p1, point p2) {return pair(p1.x, p1.y) < pair(p2.x, p2.y);});
    p.erase(unique(p.begin(), p.end()), p.end());
    return p;
}

// Segment-Point Distance: finds the shortest distance from segment ab to point p
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
    if (proper_inter(a, b, c, d).size()) return 0;
    return min({segment_point(a, b, c), segment_point(a, b, d),
                segment_point(c, d, a), segment_point(c, d, b)});
}
