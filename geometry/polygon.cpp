float area(point a, point b, point c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

float area(const vector<point> &p) {
    T a = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) a += cross(p[i], p[(i + 1) % n]);
    return abs(a) / 2.0;
}

// Pick's Theorem: calculates the area of a simple polygon with integer vertices
// Time: O(1) | Space: O(1)
// Note: i is the number of interior points, b is the number of boundary points
float picks_theorem(int i, int b) {
    return i + (b / 2.0) - 1;
}

// Boundary Points: calculates the total number of integer points on the boundary of a polygon
// Time: O(N log M) | Space: O(1)
// Note: relies on the property that the number of integer points on a segment is gcd(dx, dy)
int boundary_points(const vector<point> &g) {
    int c = 0, n = g.size();
    for (int i = 0; i < n; ++i) {
        point p = g[i], q = g[(i + 1) % n];
        c += gcd(p.x - q.x, p.y - q.y);
    }
    return c;
}

// Winding Number: computes how many times a polygon wraps around a point
// Time: O(N) | Space: O(1)
// Note: returns non-zero for inside, zero for outside or boundary
int winding_number(const vector<point> &g, point a) {
    int w = 0, n = g.size();
    for (int i = 0; i < n; ++i) {
        point p = g[i], q = g[(i + 1) % n];
        if (on_segment(p, q, a)) return 0;
        int d = (q.y >= a.y) - (p.y >= a.y);
        if (d * orient(p, q, a) > 0) w += d;
    }
    return w;
}
