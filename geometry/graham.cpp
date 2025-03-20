point p0;

int distance(point p, point q) {
    int x = p.x - q.x, y = p.y - q.y;
    return x * x + y * y;
}

bool compare(point p1, point p2) {
    int o = orient(p0, p1, p2);
    if (o == 0) return distance(p0, p1) < distance(p0, p2);
    return o == -1;
}

array<point> graham(array<point> p) {
    int n = p.size(), b = 0;
    for (int i = 1; i < n; ++i) {
        if (p[i].y < p[b].y or (p[i].y == p[b].y and p[i].x < p[b].x)) {
            b = i;
        }
    }
    swap(p[b], p[0]);
    p0 = p[0];

    sort(p.begin() + 1, p.end(), compare);
    int k; for (k = n - 1; k > 0 and orient(p0, p[k], p[n - 1]) == 0; --k);
    reverse(p.begin() + (k + 1), p.end());

    array<point> h;
    h.push_back(p[0]), h.push_back(p[1]);
    for (int i = 2; i < n; ++i) {
        while (h.size() > 1 and orient(h[h.size() - 2], h[h.size() - 1], p[i]) == 1) h.pop_back();
        h.push_back(p[i]);
    }
    return h;
}
