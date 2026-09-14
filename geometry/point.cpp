#define x real()
#define y imag()

using T = int;
using point = complex<T>;

namespace std {
    bool operator<(const point &a, const point &b) {
        return pair(a.x, a.y) < pair(b.x, b.y);
    }
}

istream &operator>>(istream &is, point &p) {
    T r, i; is >> r >> i;
    p = {r, i};
    return is;
}

int sign(T n) {
    if (n == 0) return 0;
    return n < 0 ? -1 : +1;
}

float dist(point a, point b) {
    return sqrt(norm(a - b));
}

T dot(point p, point q) {
    return (conj(p) * q).x;
}

T cross(point p, point q) {
    return (conj(p) * q).y;
}

T orient(point a, point b, point c) {
    return cross(b - a, c - a);
}

point perp(point p) {
    return {-p.y, p.x};
}

// Directed Angle: shortest angle from vector v to vector w
// Note: returns radians in [-pi, pi], negative result means w is to the right
float angle(point v, point w) {
    return atan2(cross(v, w), dot(v, w));
}
