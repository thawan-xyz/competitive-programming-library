// Venice Set: Multiset with Global Value Updates
// Time: O(log N) | Space: O(N)
struct venice_set {
    int k = 0;
    multiset<int> s;

    void insert(int x) { s.insert(x - k); }

    void remove(int x) { if (auto i = s.find(x - k); i != s.end()) s.erase(i); }

    void update(int x) { k += x; }

    int min() { return *s.begin() + k; }
};
