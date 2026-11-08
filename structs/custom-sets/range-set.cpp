// Range Set: bitset optimized for range updates and queries
// Time: O(N/64) per operation | Space: O(N/64)
// Note: uint = uint64_t (unsigned long long)
struct range_set {
    int n;
    vector<uint> data;

    range_set(int n): n(n), data((n + 63) / 64) {}

    uint from(int i) {
        return ~0ULL << (i & 63);
    }

    uint until(int i) {
        return ~0ULL >> (63 - (i & 63));
    }

    void apply(int k, bool on, uint mask) {
        if (on) data[k] |= mask;
        else data[k] &= ~mask;
    }
    
    void update(int l, int r, bool on) {
        int i = l >> 6, j = r >> 6;
        if (i == j) {
            apply(i, on, from(l) & until(r));
        } else {
            apply(i, on, from(l));
            for (int k = i + 1; k < j; ++k) apply(k, on, ~0ULL);
            apply(j, on, until(r));
        }
    }

    int count(int l, int r) {
        int c = 0;
        int i = l >> 6, j = r >> 6;
        if (i == j) {
            c = __builtin_popcountll(data[i] & (from(l) & until(r)));
        } else {
            c += __builtin_popcountll(data[i] & from(l));
            for (int k = i + 1; k < j; ++k) c += __builtin_popcountll(data[k]);
            c += __builtin_popcountll(data[j] & until(r));
        }
        return c;
    }

    bool empty() {
        for (uint mask : data) if (mask) return false;
        return true;
    }

    int prev(int i) {
        for (int k = i >> 6; k >= 0; --k, i = 63) {
            uint mask = data[k] & until(i);
            if (mask) return (k << 6) + 63 - __builtin_clzll(mask);
        }
        return n;
    }

    int next(int i) {
        for (int k = i >> 6; k < data.size(); ++k, i = 0) {
            uint mask = data[k] & from(i);
            if (mask) return (k << 6) + __builtin_ctzll(mask);
        }
        return n;
    }

    int segments() {
        int s = 0;
        for (int k = 0; k < data.size(); ++k) {
            s += __builtin_popcountll((data[k] >> 1) & ~data[k]);
            if ((data[k] & 1) and (k == 0 or (data[k - 1] >> 63) == 0)) s += 1;
        }
        return s;
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
