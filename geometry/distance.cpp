float point(point p, point q) {
    return norm(p - q);
}

float line(point p, point s1, point s2) {
    return abs(cross(s1, s2, p)) / norm(s1 - s2);
}
