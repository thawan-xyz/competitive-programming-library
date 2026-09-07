#define x real()
#define y imag()

using T = float;
using point = complex<T>;

// Dot: calculates the dot (scalar) product of vectors p and q
// Note: > 0 if acute angle, < 0 if obtuse, 0 if orthogonal (perpendicular)
T dot(point p, point q) {
    return (conj(p) * q).x;
}

// Cross: calculates the 2D cross product (determinant) of vectors p and q
// Note: > 0 if q is counter-clockwise from p, 0 if colinear (magnitude is parallelogram area)
T cross(point p, point q) {
    return (conj(p) * q).y;
}

// Perpendicular: rotates the vector p by 90 degrees counter-clockwise
// Note: mathematically equivalent to multiplying the complex number by i
point perp(point p) {
    return {-p.y, p.x};
}

// Directed Angle: shortest angle from vector v to vector w
// Note: returns radians in [-pi, pi] | negative result means w is to the right
float angle(point v, point w) {
    return atan2(cross(v, w), dot(v, w));
}

// Half: determines which half-plane a point lies in relative to ray v
// Note: returns 0 for [0, pi) relative to v (including origin), 1 for [pi, 2pi)
bool half(point p, point v) {
    T c = cross(v, p);
    T d = dot(v, p);
    return c < 0 or (c == 0 and d < 0);
}

// Polar Sort: sorts points counter-clockwise around an origin starting at reference ray v
// Time: O(N log N) | Space: O(1)
// Note: colinear points sorted by distance | exact integer arithmetic
void polar_sort(vector<point> &p, point o = {0, 0}, point v = {1, 0}) {
    sort(p.begin(), p.end(), [&](point a, point b) {
        a = a - o, b = b - o;
        bool ha = half(a, v), hb = half(b, v);
        if (ha != hb) return ha < hb;
        T c = cross(a, b);
        if (c != 0) return c > 0;
        return norm(a) < norm(b);
    });
}
