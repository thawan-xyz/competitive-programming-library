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
// Note: returns radians in [-PI, PI] | negative result means w is to the right
template <typename T>
double angle(point<T> v, point<T> w) {
    return atan2(cross(v, w), dot(v, w));
}
