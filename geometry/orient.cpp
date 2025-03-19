int orient(point &p1, point &p2, point &p3) {
    int o = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
    return (o < 0) ? -1 : ((o > 0) ? 1 : 0);
}
