point incircle(point a, point b, point c) {
    assert(is_floating_point_v<T>);
    T ab = sqrt(dist2(a, b)), bc = sqrt(dist2(b, c)), ac = sqrt(dist2(a, c)), p = ab + bc + ac;
    if (sign(p) == 0) return {};
    return (a * bc + b * ac + c * ab) / p;
}

point circumcircle(point a, point b, point c) {
    assert(is_floating_point_v<T>);
    point v = b - a, w = c - a;
    T h = cross(v, w);
    if (sign(h) == 0) return {};
    return a + perp(v * norm(w) - w * norm(v)) / (2 * h);
}

// Minimum Enclosing Circle: smallest circle that contains all points, returns {o, r}
// Time: O(N) expected | Space: O(N)
// Note: shuffles a copy of the points, every point that falls outside is on the border of the new circle
pair<point, T> min_enclosing_circle(vector<point> p) {
    assert(is_floating_point_v<T>);
    shuffle(p.begin(), p.end(), rng);
    point o = p[0];
    T r2 = 0;
    auto out = [&](point q) { return sign(dist2(o, q) - r2) > 0; };
    for (int i = 0; i < p.size(); ++i) if (out(p[i])) {
        o = p[i], r2 = 0;
        for (int j = 0; j < i; ++j) if (out(p[j])) {
            o = (p[i] + p[j]) / T(2), r2 = dist2(o, p[i]);
            for (int k = 0; k < j; ++k) if (out(p[k])) o = circumcircle(p[i], p[j], p[k]), r2 = dist2(o, p[i]);
        }
    }
    return {o, T(sqrt(r2))};
}

vector<point> circle_line_inter(point o, T r, line l) {
    assert(is_floating_point_v<T>);
    T h2 = r * r - l.side(o) * l.side(o) / norm(l.v);
    if (sign(h2) < 0) return {};
    point p = l.proj(o);
    if (sign(h2) == 0) return {p};
    point h = l.v * T(sqrt(h2 / norm(l.v)));
    return {p - h, p + h};
}

vector<point> circle_segment_inter(point o, T r, point a, point b) {
    assert(is_floating_point_v<T>);
    if (a == b) {
        if (sign(dist2(a, o) - r * r) == 0) return {a};
        return {};
    }
    vector<point> h;
    for (point p : circle_line_inter(o, r, line(a, b))) if (in_disk(a, b, p)) h.push_back(p);
    return h;
}

vector<point> circle_inter(point o1, T r1, point o2, T r2) {
    assert(is_floating_point_v<T>);
    point v = o2 - o1;
    T d2 = norm(v);
    if (sign(d2) == 0) return {};
    T op = (d2 + r1 * r1 - r2 * r2) / 2, h2 = r1 * r1 - op * op / d2;
    if (sign(h2) < 0) return {};
    point p = o1 + v * (op / d2);
    if (sign(h2) == 0) return {p};
    point h = perp(v) * T(sqrt(h2 / d2));
    return {p - h, p + h};
}

T circle_inter_area(point o1, T r1, point o2, T r2) {
    assert(is_floating_point_v<T>);
    T d = sqrt(dist2(o1, o2));
    if (sign(d - r1 - r2) >= 0) return 0;
    if (sign(d - abs(r1 - r2)) <= 0) return acos(T(-1)) * min(r1, r2) * min(r1, r2);
    T h1 = 2 * acos(clamp((d * d + r1 * r1 - r2 * r2) / (2 * d * r1), T(-1), T(1)));
    T h2 = 2 * acos(clamp((d * d + r2 * r2 - r1 * r1) / (2 * d * r2), T(-1), T(1)));
    return (r1 * r1 * (h1 - sin(h1)) + r2 * r2 * (h2 - sin(h2))) / 2;
}

vector<point> circle_tangents(point o, T r, point p) {
    assert(is_floating_point_v<T>);
    point v = p - o;
    T d2 = norm(v), h2 = d2 - r * r;
    if (sign(h2) < 0) return {};
    point q = o + v * (r * r / d2);
    if (sign(h2) == 0) return {q};
    point h = perp(v) * T(r * sqrt(h2) / d2);
    return {q - h, q + h};
}

vector<pair<point, point>> circle_circle_tangents(point o1, T r1, point o2, T r2) {
    assert(is_floating_point_v<T>);
    point v = o2 - o1;
    T d2 = norm(v);
    if (sign(d2) == 0) return {};
    vector<pair<point, point>> res;
    for (T s : {T(1), T(-1)}) {
        T dr = r1 - s * r2, h2 = d2 - dr * dr;
        if (sign(h2) < 0) continue;
        for (T t : {T(-1), T(1)}) {
            point w = (v * dr + perp(v) * T(t * sqrt(max(h2, T(0))))) / d2;
            res.push_back({o1 + w * r1, o2 + w * (s * r2)});
            if (sign(h2) == 0) break;
        }
    }
    return res;
}
