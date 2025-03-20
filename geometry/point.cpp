struct point {
    int x, y;
    
    point operator - (const point &other) const {
        return {x - other.x, y - other.y};
    }
};

int cross(point &p1, point &p2, point &p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

float norm(point &p) {
    return sqrt(p.x * p.x + p.y * p.y);
}
