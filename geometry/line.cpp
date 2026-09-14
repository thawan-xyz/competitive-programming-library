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

    bool comp(point p, point q) {
        return dot(v, p) < dot(v, q);
    }

    // Projection: calculates the orthogonal projection of point p onto the line
    // Note: translates p perpendicularly to the line (assumes perp is counter-clockwise)
    point proj(point p) {
        return p - (perp(v) * side(p)) / norm(v);
    }

    // Reflection: finds the mirror image of point p across the line
    // Note: projects p and extends it by the same distance
    point refl(point p) {
        return p - (2.0 * perp(v) * side(p)) / norm(v);
    }
};

vector<point> line_inter(line l, line r) {
    if (cross(l.v, r.v) == 0) return {};
    return {(l.c * r.v - r.c * l.v) / cross(l.v, r.v)};
}

vector<point> line_segment_inter(line l, point a, point b) {
    T sa = l.side(a);
    T sb = l.side(b);
    if (sign(sa) * sign(sb) > 0) return {};
    if (sa == 0 and sb == 0) {
        vector<point> p = {a, b};
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        return p;
    }
    return {(a * sb - b * sa) / (sb - sa)};
}
