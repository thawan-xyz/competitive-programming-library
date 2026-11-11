#define x real()
#define y imag()

using T = int;
using point = complex<T>;

int sign(T v) {
    if constexpr (is_floating_point_v<T>) return (v > 1e-9) - (v < -1e-9);
    else return (v > 0) - (v < 0);
}

namespace std {
    bool operator<(const point &a, const point &b) {
        return pair(a.x, a.y) < pair(b.x, b.y);
    }

    bool operator==(const point &a, const point &b) {
        return sign(a.x - b.x) == 0 and sign(a.y - b.y) == 0;
    }
}

istream &operator>>(istream &is, point &p) {
    T r, i;
    is >> r >> i;
    p = {r, i};
    return is;
}

T dist2(point a, point b) {
    return norm(a - b);
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

// Rotate: rotates p by a radians counter-clockwise
point rotate(point p, T a) {
    assert(is_floating_point_v<T>);
    return p * polar(T(1), a);
}

// Directed Angle: shortest angle from vector v to vector w
// Note: returns radians in [-pi, pi], negative result means w is to the right
float angle(point v, point w) {
    return atan2(cross(v, w), dot(v, w));
}

bool is_upper(point p, point v) {
    int c = sign(cross(v, p));
    return c > 0 or (c == 0 and sign(dot(v, p)) < 0);
}

// Polar Sort: sorts points counter-clockwise around o, starting right after the direction opposite to v
// Time: O(N log N) | Space: O(1)
// Note: exact with integer T | collinear points in the same direction are sorted by distance, and o itself comes first
void polar_sort(vector<point> &p, point o = {0, 0}, point v = {1, 0}) {
    sort(p.begin(), p.end(), [&](point a, point b) {
        a = a - o, b = b - o;
        bool ha = is_upper(a, v), hb = is_upper(b, v);
        if (ha != hb) return ha < hb;
        int c = sign(cross(a, b));
        if (c != 0) return c > 0;
        return norm(a) < norm(b);
    });
}

// Closest Pair: smallest squared distance between two of the points, sweeping by x with the active points sorted by y
// Time: O(N log N) | Space: O(N)
// Note: needs at least two points | returns {d2, i, j}, with i and j the indices of the pair
tuple<T, int, int> closest_pair(vector<point> &p) {
    int n = p.size();
    vector<int> id(n);
    iota(id.begin(), id.end(), 0);
    sort(id.begin(), id.end(), [&](int i, int j) { return p[i] < p[j]; });
    T best = dist2(p[0], p[1]);
    int i = 0, j = 1;
    set<pair<T, int>> active;
    for (int r = 0, l = 0; r < n; ++r) {
        point q = p[id[r]];
        while (l < r and (q.x - p[id[l]].x) * (q.x - p[id[l]].x) >= best) active.erase({p[id[l]].y, id[l]}), l++;
        T d = sqrtl(best) + 1;
        for (auto itr = active.lower_bound({q.y - d, -1}); itr != active.end() and itr->first <= q.y + d; ++itr) {
            T c = dist2(q, p[itr->second]);
            if (c < best) best = c, i = itr->second, j = id[r];
        }
        active.insert({q.y, id[r]});
    }
    return {best, i, j};
}
