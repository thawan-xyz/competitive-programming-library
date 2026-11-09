// Interval Set: maintains disjoint intervals with dynamic active elements count
// Time: insert/remove O(log N) amortized | contains O(log N) | total O(1) | Space: O(N)
// Note: discrete=true for [l, r] (r-l+1) | discrete=false for continuous [l, r) (r-l)
struct interval_set {
    int active = 0, off;
    set<pair<int, int>> s;

    interval_set(bool discrete): off(discrete) {}

    void insert(int l, int r) {
        assert(l < r + off);
        auto itr = s.lower_bound({l, -inf});
        if (itr != s.begin() and prev(itr)->second >= l - off) itr--;
        int nl = l;
        int nr = r;
        while (itr != s.end() and itr->first <= r + off) {
            nl = min(nl, itr->first);
            nr = max(nr, itr->second);
            active -= itr->second - itr->first + off;
            itr = s.erase(itr);
        }
        active += nr - nl + off;
        s.insert({nl, nr});
    }

    void remove(int l, int r) {
        assert(l < r + off);
        auto itr = s.lower_bound({l, -inf});
        if (itr != s.begin() and prev(itr)->second >= l) itr--;
        while (itr != s.end() and itr->first <= r) {
            int cl = itr->first;
            int cr = itr->second;
            active -= cr - cl + off;
            itr = s.erase(itr);
            if (cl < l) {
                s.insert({cl, l - off});
                active += l - cl;
            }
            if (cr > r) {
                s.insert({r + off, cr});
                active += cr - r;
            }
        }
    }

    bool contains(int l, int r) {
        assert(l < r + off);
        auto itr = s.upper_bound({l, inf});
        if (itr == s.begin()) return false;
        itr--;
        return itr->first <= l and r <= itr->second;
    }

    int total() {
        return active;
    }
};

// Color Set: disjoint intervals [l, r], each with a color, painting a range and returning what was there before, with lazy moves of all positions
// Time: paint and erase O(log N) amortized | contains and color O(log N) | shift and flip O(1) | Space: O(N)
// Note: real position = sign * stored + offset | shift(k) = x -> x + k, flip(c) = x -> c - x (flip(l + r) mirrors [l, r])
struct color_set {
    struct node {
        int l, r, color;
    };

    map<int, node> s;
    int sign = 1, offset = 0;

    int stored(int x) {
        return sign * (x - offset);
    }

    node real(node a) {
        int l = sign * a.l + offset, r = sign * a.r + offset;
        a.l = min(l, r), a.r = max(l, r);
        return a;
    }

    void split(int x) {
        auto it = s.lower_bound(x);
        if (it == s.begin()) return;
        node &a = (--it)->second;
        if (x <= a.r) {
            node b = a;
            b.l = x, a.r = x - 1;
            s[x] = b;
        }
    }

    vector<node> erase(int l, int r) {
        if (l > r) return {};
        int a = min(stored(l), stored(r)), b = max(stored(l), stored(r));
        split(a), split(b + 1);
        vector<node> removed;
        auto first = s.lower_bound(a), last = s.lower_bound(b + 1);
        for (auto it = first; it != last; ++it) removed.push_back(real(it->second));
        s.erase(first, last);
        if (sign == -1) reverse(removed.begin(), removed.end());
        return removed;
    }

    vector<node> paint(int l, int r, int c) {
        if (l > r) return {};
        vector<node> removed = erase(l, r);
        int a = min(stored(l), stored(r)), b = max(stored(l), stored(r));
        s[a] = {a, b, c};
        return removed;
    }

    bool contains(int x) {
        auto it = s.upper_bound(stored(x));
        return it != s.begin() and prev(it)->second.r >= stored(x);
    }

    int color(int x) {
        return prev(s.upper_bound(stored(x)))->second.color;
    }

    void shift(int k) {
        offset += k;
    }

    void flip(int c) {
        sign = -sign, offset = c - offset;
    }
};
