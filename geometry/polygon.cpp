float triangle_area(point a, point b, point c) {
    return abs(cross(b - a, c - a)) / 2.0;
}

float polygon_area(const vector<point> &p) {
    T area = 0;
    int n = p.size();
    for (int i = 0; i < n; ++i) area += cross(p[i], p[(i + 1) % n]);
    return abs(area) / 2.0;
}
