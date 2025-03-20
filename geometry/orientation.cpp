int orient(point p1, point p2, point p3) {
    int c = cross(p1, p2, p3);
    return (c < 0) - (c > 0);
}
