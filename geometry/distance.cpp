double point_line(point &s1, point &s2, point &p) {
    return abs(cross(s1, s2, p)) / norm(s1 - s2);
}
