array<point> convex_hull(array<point> &p) {
    int n = p.size();
    sort(p.begin(), p.end());

    int h = 0;
    array<point> lower;
    for (int i = 0; i < n; ++i) {
        while (h >= 2) {
            line l = {lower[h - 2], lower[h - 1]};
            if (l.orient(p[i]) == -1) break;
            lower.pop_back();
            h--;
        }
        lower.push_back(p[i]);
        h++;
    }

    int k = 0;
    array<point> upper;
    for (int i = n - 1; i >= 0; --i) {
        while (k >= 2) {
            line l = {upper[k - 2], upper[k - 1]};
            if (l.orient(p[i]) == -1) break;
            upper.pop_back();
            k--;
        }
        upper.push_back(p[i]);
        k++;
    }

    lower.pop_back();
    upper.pop_back();

    array<point> hull = lower;
    hull.insert(hull.end(), upper.begin(), upper.end());
    return hull;
}
