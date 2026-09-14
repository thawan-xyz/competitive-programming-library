// Is Upper: determines which half-plane a point lies in relative to ray v
// Note: returns 1 for (0, pi] (upper half and opposite ray), 0 for (pi, 2pi] (lower half, ray v and origin)
bool is_upper(point p, point v) {
    T c = cross(v, p);
    T d = dot(v, p);
    return c > 0 or (c == 0 and d < 0);
}

// Polar Sort: sorts points counter-clockwise starting from the opposite of reference ray v
// Time: O(N log N) | Space: O(1)
// Note: colinear points sorted by distance
void polar_sort(vector<point> &p, point o = {0, 0}, point v = {1, 0}) {
    sort(p.begin(), p.end(), [&](point a, point b) {
        a = a - o, b = b - o;
        bool ha = is_upper(a, v), hb = is_upper(b, v);
        if (ha != hb) return ha < hb;
        T c = cross(a, b);
        if (c != 0) return c > 0;
        return norm(a) < norm(b);
    });
}
