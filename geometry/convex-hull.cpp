array<point> convex_hull(array<point> &p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    int n = p.size();
    if (n < 3) return p;

    bool collinear = true;
    line h = {p[0], p[1]};
    for (int i = 2; i < n and collinear; ++i) collinear &= h.orient(p[i]) == 0;
    if (collinear) return {p[0], p[n - 1]};

    array<point> lower;
    for (int i = 0; i < n; ++i) {
        while (lower.size() >= 2) {
            line l = {lower[lower.size() - 2], lower[lower.size() - 1]};
            if (l.orient(p[i]) == -1) break;
            lower.pop_back();
        }
        lower.push_back(p[i]);
    }

    array<point> upper;
    for (int i = n - 1; i >= 0; --i) {
        while (upper.size() >= 2) {
            line l = {upper[upper.size() - 2], upper[upper.size() - 1]};
            if (l.orient(p[i]) == -1) break;
            upper.pop_back();
        }
        upper.push_back(p[i]);
    }

    lower.pop_back();
    upper.pop_back();

    array<point> hull = lower;
    hull.insert(hull.end(), upper.begin(), upper.end());
    return hull;
}
