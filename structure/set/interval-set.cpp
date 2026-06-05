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
