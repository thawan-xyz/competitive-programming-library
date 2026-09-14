struct line {
    point v;
    T c;

    line(point v, T c): v(v), c(c) {}

    line(T a, T b, T c): v({b, -a}), c(c) {}

    line(point p, point q): v(q - p), c(cross(q, p)) {}

    // Side: evaluates the relative position of point p to the directed line
    // Note: > 0 if left, < 0 if right, 0 if colinear (magnitude proportional to distance)
    T side(point p) {
        return cross(v, p) - c;
    }

    // Distance: calculates the shortest euclidean distance from p to the line
    // Note: normalizes side magnitude to return the exact non-negative distance
    float dist(point p) {
        return abs(side(p)) / sqrt(norm(v));
    }

    // Compare: sorts points based on their orthogonal projection along the line
    // Note: returns true if p is before q in the direction of v
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

// Line Intersection: finds the unique intersection point of two lines
// Note: returns a single point if they cross, or empty if they are parallel or coincident
vector<point> line_inter(line l, line r) {
    if (cross(l.v, r.v) == 0) return {};
    return {(l.c * r.v - r.c * l.v) / cross(l.v, r.v)};
}

// Line-Segment Intersection: finds the intersection between line l and segment ab
// Note: returns empty if no intersection, 1 point if they cross, or 2 points if collinear
vector<point> line_segment_inter(line l, point a, point b) {
    T sa = l.side(a);
    T sb = l.side(b);
    if (sign(sa) * sign(sb) > 0) return {};
    if (sa == 0 and sb == 0) {
        vector<point> pts = {a, b};
        sort(pts.begin(), pts.end(), [&](point p1, point p2) {
            return pair(p1.x, p1.y) < pair(p2.x, p2.y);
        });
        pts.erase(unique(pts.begin(), pts.end()), pts.end());
        return pts;
    }
    return {(a * sb - b * sa) / (sb - sa)};
}
