float area(vector<point> &p) {
    int n = p.size();
    float a = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        a += p[i].x * p[j].y - p[j].x * p[i].y;
    }
    return a / 2;
}

vector<point> convex_hull(vector<point> &p, bool collinear) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());

    int n = p.size();
    if (n <= 2) return p;

    bool all_collinear = true;
    line h = {p[0], p[1]};
    for (int i = 2; i < n and all_collinear; ++i) all_collinear &= h.orientation(p[i]) == 0;
    if (all_collinear) return collinear ? p : vector<point>{p[0], p[n - 1]};

    vector<point> lower;
    for (int i = 0; i < n; ++i) {
        while (lower.size() >= 2) {
            line l = {lower[lower.size() - 2], lower[lower.size() - 1]};
            int o = l.orientation(p[i]);
            if (o == -1 or (o == 0 and collinear)) break;
            lower.pop_back();
        }
        lower.push_back(p[i]);
    }

    vector<point> upper;
    for (int i = n - 1; i >= 0; --i) {
        while (upper.size() >= 2) {
            line l = {upper[upper.size() - 2], upper[upper.size() - 1]};
            int o = l.orientation(p[i]);
            if (o == -1 or (o == 0 and collinear)) break;
            upper.pop_back();
        }
        upper.push_back(p[i]);
    }

    lower.pop_back();
    upper.pop_back();

    vector<point> hull = lower;
    hull.insert(hull.end(), upper.begin(), upper.end());
    return hull;
}
