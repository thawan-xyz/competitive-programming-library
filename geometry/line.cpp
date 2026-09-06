struct line {
    point v;
    T c;

    line(point v, T c): v(v), c(c) {}

    line(T a, T b, T c): v({b, -a}), c(c) {}

    line(point p, point q): v(q - p), c(cross(q, p)) {}

    T side(point p) {
        return cross(v, p) - c;
    }

    float dist(point p) {
        return abs(side(p)) / sqrt(norm(v));
    }

    bool compare(point p, point q) {
        return dot(v, p) < dot(v, q);
    }
};

complex<float> intersection(line l1, line l2) {
    complex<float> num = l1.c * complex<float>(l2.v) - l2.c * complex<float>(l1.v);
    float den = cross(l1.v, l2.v);
    return num / den;
}
