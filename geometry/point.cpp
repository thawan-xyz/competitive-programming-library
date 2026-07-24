#define x real()
#define y imag()

template <typename T>
using point = complex<T>;

template <typename T>
T dot(point<T> p, point<T> q) {
    return (conj(p) * q).x;
}

template <typename T>
T cross(point<T> p, point<T> q) {
    return (conj(p) * q).y;
}

// Directed Angle: shortest angle from vector v to vector w
// Note: returns radians in [-pi, pi] | negative result means w is to the right
template <typename T>
double angle(point<T> v, point<T> w) {
    return atan2(cross(v, w), dot(v, w));
}

// Half: determines which half-plane a point lies in relative to ray v
// Note: returns 0 for [0, pi) relative to v (including origin), 1 for [pi, 2pi)
template <typename T>
bool half(point<T> p, point<T> v) {
    T c = cross(v, p);
    T d = dot(v, p);
    return c < 0 or (c == 0 and d < 0);
}

// Polar Sort: sorts points counter-clockwise around an origin starting at reference ray v
// Time: O(N log N) | Space: O(1)
// Note: colinear points sorted by distance | exact integer arithmetic
template <typename T>
void polar_sort(vector<point<T>> &p, point<T> o = {0, 0}, point<T> v = {1, 0}) {
    sort(p.begin(), p.end(), [&](point<T> a, point<T> b) {
        a = a - o, b = b - o;
        bool ha = half(a, v), hb = half(b, v);
        if (ha != hb) return ha < hb;
        T c = cross(a, b);
        if (c != 0) return c > 0;
        return norm(a) < norm(b);
    });
}
