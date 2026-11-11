struct line {
    point v;
    T c;

    line(point v, T c): v(v), c(c) {}

    line(T a, T b, T c): v(b, -a), c(c) {}

    line(point p, point q): v(q - p), c(cross(v, p)) {}

    T side(point p) {
        return cross(v, p) - c;
    }

    float dist(point p) {
        return abs(side(p)) / sqrt(norm(v));
    }

    bool comp(point p, point q) {
        return dot(v, p) < dot(v, q);
    }

    line perp_through(point p) {
        return line(p, p + perp(v));
    }

    line parallel_through(point p) {
        return line(v, cross(v, p));
    }

    line shift(T t) {
        assert(is_floating_point_v<T>);
        return line(v, c + t * abs(v));
    }

    point proj(point p) {
        assert(is_floating_point_v<T>);
        return p - perp(v) * side(p) / norm(v);
    }

    point refl(point p) {
        assert(is_floating_point_v<T>);
        return p - perp(v) * (2 * side(p)) / norm(v);
    }
};

vector<point> line_inter(line l, line r) {
    assert(is_floating_point_v<T>);
    T d = cross(l.v, r.v);
    if (sign(d) == 0) return {};
    return {(r.v * l.c - l.v * r.c) / d};
}

vector<point> line_segment_inter(line l, point a, point b) {
    assert(is_floating_point_v<T>);
    T sa = l.side(a), sb = l.side(b);
    if (sign(sa) * sign(sb) > 0) return {};
    if (sign(sa) == 0 and sign(sb) == 0) {
        if (b < a) swap(a, b);
        if (a == b) return {a};
        return {a, b};
    }
    return {(a * sb - b * sa) / (sb - sa)};
}
