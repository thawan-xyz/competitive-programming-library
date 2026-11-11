// Polygon: area, integer points, point in polygon and convex hull, with the vertices in order, plus point in convex polygon, farthest pair, cut and Minkowski sum
// Time: O(N), O(N log N) for the hull and the farthest pair, O(log N) for in_convex | Space: O(N)
// Note: requires point, line and segment | exact with integer T, except polygon_cut
float area(point a, point b, point c) {
    return abs(orient(a, b, c)) / 2.0;
}

float area(const vector<point> &p) {
    T a = 0;
    for (int i = 0, n = p.size(); i < n; ++i) a += cross(p[i], p[(i + 1) % n]);
    return abs(a) / 2.0;
}

// Pick's Theorem: area of a simple polygon with integer vertices, from i interior and b boundary integer points
// Note: interior points of a polygon = area - b / 2 + 1
float picks_theorem(int i, int b) {
    return i + b / 2.0 - 1;
}

// Boundary Points: number of integer points on the boundary of a polygon with integer vertices
// Time: O(N log C) | Space: O(1)
// Note: a segment from p to q has gcd(|dx|, |dy|) integer points, counting one of its ends
int boundary_points(const vector<point> &p) {
    int c = 0;
    for (int i = 0, n = p.size(); i < n; ++i) c += gcd((long long) (p[i].x - p[(i + 1) % n].x), (long long) (p[i].y - p[(i + 1) % n].y));
    return c;
}

// Winding Number: how many times the polygon turns around point a
// Time: O(N) | Space: O(1)
// Note: non-zero inside, zero outside or on the boundary
int winding_number(const vector<point> &p, point a) {
    int w = 0;
    for (int i = 0, n = p.size(); i < n; ++i) {
        point s = p[i], t = p[(i + 1) % n];
        if (on_segment(s, t, a)) return 0;
        int d = (t.y >= a.y) - (s.y >= a.y);
        if (d * sign(orient(s, t, a)) > 0) w += d;
    }
    return w;
}

// Convex Hull: monotone chain, counter-clockwise from the smallest point
// Time: O(N log N) | Space: O(N)
// Note: col keeps the collinear points on the edges | if all points are collinear, col returns all of them sorted
vector<point> convex_hull(vector<point> p, bool col) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size(), lim = not col;
    if (n < 3) return p;
    bool all = col;
    for (int i = 2; i < n; ++i) all &= sign(orient(p[0], p[1], p[i])) == 0;
    if (all) return p;
    vector<point> h;
    for (int k = 0; k < 2; ++k) {
        int s = h.size();
        for (point q : p) {
            while (h.size() >= s + 2 and sign(orient(h[h.size() - 2], h.back(), q)) < lim) h.pop_back();
            h.push_back(q);
        }
        h.pop_back();
        reverse(p.begin(), p.end());
    }
    return h;
}

// Point in Convex Polygon: binary search on the fan of triangles from p[0]
// Time: O(log N) | Space: O(1)
// Note: p strictly convex and counter-clockwise, like convex_hull(p, false) | returns 1 inside, 0 on the boundary, -1 outside
int in_convex(const vector<point> &p, point a) {
    int n = p.size();
    if (n < 3) return on_segment(p[0], p.back(), a) ? 0 : -1;
    if (sign(orient(p[0], p[1], a)) < 0 or sign(orient(p[0], p[n - 1], a)) > 0) return -1;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (sign(orient(p[0], p[m], a)) >= 0) l = m;
        else r = m;
    }
    int s = sign(orient(p[l], p[l + 1], a));
    if (s < 0) return -1;
    if (s == 0 or (l == 1 and sign(orient(p[0], p[1], a)) == 0) or (l == n - 2 and sign(orient(p[0], p[n - 1], a)) == 0)) return 0;
    return 1;
}

// Farthest Pair: largest squared distance between two of the points, with rotating calipers on the convex hull
// Time: O(N log N) | Space: O(N)
// Note: for each edge of the hull, j walks to the farthest point from it, and it only moves forward
T farthest_pair(const vector<point> &p) {
    vector<point> h = convex_hull(p, false);
    int n = h.size();
    if (n < 3) return dist2(h[0], h.back());
    T best = 0;
    for (int i = 0, j = 1; i < n; ++i) {
        while (sign(cross(h[(i + 1) % n] - h[i], h[(j + 1) % n] - h[j])) > 0) j = (j + 1) % n;
        best = max({best, dist2(h[i], h[j]), dist2(h[(i + 1) % n], h[j])});
    }
    return best;
}

// Polygon Cut: the part of a convex polygon to the left of line l, side >= 0
// Time: O(N) | Space: O(N)
// Note: requires line | asserts that T is floating point
vector<point> polygon_cut(const vector<point> &p, line l) {
    assert(is_floating_point_v<T>);
    vector<point> res;
    for (int i = 0, n = p.size(); i < n; ++i) {
        point a = p[i], b = p[(i + 1) % n];
        int sa = sign(l.side(a)), sb = sign(l.side(b));
        if (sa >= 0) res.push_back(a);
        if (sa * sb < 0) res.push_back(line_segment_inter(l, a, b)[0]);
    }
    return res;
}

// Minkowski Sum: the convex polygon of all sums a + b with a in p and b in q, merging the edges by angle
// Time: O(N + M) | Space: O(N + M)
// Note: p and q strictly convex and counter-clockwise, like convex_hull(p, false) | exact with integer T
vector<point> minkowski(vector<point> p, vector<point> q) {
    for (auto *v : {&p, &q}) {
        rotate(v->begin(), min_element(v->begin(), v->end()), v->end());
        v->push_back((*v)[0]), v->push_back((*v)[1]);
    }
    vector<point> res;
    for (int i = 0, j = 0; i < p.size() - 2 or j < q.size() - 2;) {
        res.push_back(p[i] + q[j]);
        int c = sign(cross(p[i + 1] - p[i], q[j + 1] - q[j]));
        if (c >= 0 and i < p.size() - 2) ++i;
        if (c <= 0 and j < q.size() - 2) ++j;
    }
    return res;
}
