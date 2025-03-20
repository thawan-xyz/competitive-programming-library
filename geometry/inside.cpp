bool triangle(point a, point b, point c, point p) {
    int o1 = orient(a, b, p);
    if (o1 == 0 and between(a, b, p)) return true;

    int o2 = orient(b, c, p);
    if (o2 == 0 and between(b, c, p)) return true;

    int o3 = orient(c, a, p);
    if (o3 == 0 and between(c, a, p)) return true;

    return o1 == o2 and o2 == o3;
}

bool convex(array<point> polygon, point p) {
    int n = polygon.size();
    if (n <= 0) return false;
    if (n == 1) return polygon[0] == p;
    if (n == 2) return orient(polygon[0], polygon[1], p) == 0 and between(polygon[0], polygon[1], p);

    if (orient(polygon[0], polygon[1], p) == 1 or orient(polygon[0], polygon[n - 1], p) == -1) return false;

    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (orient(polygon[0], polygon[m], p) == 1) {
            l = m;
        } else {
            r = m;
        }
    }
    r = l + 1 == n ? 0 : l + 1;

    return triangle(polygon[0], polygon[l], polygon[r], p);
}

bool concave(array<point> polygon, point p) {
    int n = polygon.size();
    if (n == 1) return polygon[0] == p;

    int w = 0;
    for (int i = 0; i < n; ++i) {
        point a = polygon[i], b = polygon[(i + 1) % n];
        int o = orient(a, b, p);

        if (o == 0 and between(a, b, p)) return true;

        if (a.y <= p.y and b.y > p.y and o == -1) w++;
        if (a.y > p.y and b.y <= p.y and o == 1) w--;
    }
    return w != 0;
}
