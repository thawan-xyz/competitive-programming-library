#define x real()
#define y imag()

using T = int;
using point = complex<T>;

namespace std {
    bool operator<(const point &a, const point &b) {
        return pair(a.x, a.y) < pair(b.x, b.y);
    }
}

istream &operator>>(istream &is, point &p) {
    T r, i; is >> r >> i;
    p = {r, i};
    return is;
}

int sign(T n) {
    if (n == 0) return 0;
    return n < 0 ? -1 : +1;
}

float dist(point a, point b) {
    return sqrt(norm(a - b));
}

T dot(point p, point q) {
    return (conj(p) * q).x;
}

T cross(point p, point q) {
    return (conj(p) * q).y;
}

T orient(point a, point b, point c) {
    return cross(b - a, c - a);
}

point perp(point p) {
    return {-p.y, p.x};
}

// Directed Angle: shortest angle from vector v to vector w
// Note: returns radians in [-pi, pi], negative result means w is to the right
float angle(point v, point w) {
    return atan2(cross(v, w), dot(v, w));
}

float closest_pair(vector<point> p) {
    int n = p.size();
    sort(p.begin(), p.end());
    auto compare = [](const point &a, const point &b) {
        if (a.y != b.y) return a.y < b.y;
        return a.x < b.x;
    };
    multiset<point, decltype(compare)> active(compare);
    active.insert(p[0]);
    float d = inf;
    int l = 0;
    for (int i = 1; i < n; ++i) {
        while (l < i and p[i].x - p[l].x >= d) {
            active.erase(active.find(p[l]));
            l++;
        }
        auto begin = active.lower_bound({p[i].x - d, p[i].y - d});
        auto end = active.upper_bound({p[i].x + d, p[i].y + d});
        for (auto itr = begin; itr != end; ++itr) {
            float c = dist(p[i], *itr);
            d = min(d, c);
        }
        active.insert(p[i]);
    }
    return d;
}
