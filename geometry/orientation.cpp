int orient(point &p1, point &p2, point &p3) {
    int cross = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    return (cross > 0) ? -1 : ((cross == 0) ? 0 : 1);
}
