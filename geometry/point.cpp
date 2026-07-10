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
