bool between(point p, point q, point r) {
    return r.x >= min(p.x, q.x) and r.x <= max(p.x, q.x) and r.y >= min(p.y, q.y) and r.y <= max(p.y, q.y);
}

bool intersect(point p1, point q1, point p2, point q2) {
    int o1 = orientation(p1, p2, q1);
    if (o1 == 0 and between(p1, q1, p2)) return true;

    int o2 = orientation(p1, q2, q1);
    if (o2 == 0 and between(p1, q1, q2)) return true;

    int o3 = orientation(p2, p1, q2);
    if (o3 == 0 and between(p2, q2, p1)) return true;

    int o4 = orientation(p2, q1, q2);
    if (o4 == 0 and between(p2, q2, q1)) return true;

    return o1 != o2 and o3 != o4;
}
