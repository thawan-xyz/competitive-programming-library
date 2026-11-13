// Dont Cares: splits [l, r] into aligned blocks, each with a fixed prefix and free low bits (don't cares)
// Time: O(log(r - l + 1)) | Space: O(log(r - l + 1))
// Note: 0 <= l <= r | blocks are disjoint and sorted, at most 2 per bit | bit(i) is 0 or 1 if fixed, -1 if don't care
struct pattern {
    int low, free;

    int high() const {return low | ((1LL << free) - 1);}

    int size() const {return 1LL << free;}

    int bit(int i) const {return i < free ? -1 : (low >> i) & 1;}

    bool contains(int x) const {return (x >> free) == (low >> free);}

    int count(int i, int b) const {return i < free ? size() / 2 : bit(i) == b ? size() : 0;}
};

vector<pattern> decompose(int l, int r) {
    vector<pattern> p;
    while (l <= r) {
        int k = __lg(r - l + 1);
        if (l != 0) k = min<int>(k, __builtin_ctzll(l));
        p.push_back({l, k});
        l = p.back().high() + 1;
    }
    return p;
}
