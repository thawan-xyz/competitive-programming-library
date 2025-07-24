template <typename T>
struct venice_set {
    multiset<T> s;
    T k = 0;

    int size() {
        return s.size();
    }

    void insert(T x) {
        s.insert(x + k);
    }

    void remove(T x) {
        auto i = s.find(x + k);
        if (i != s.end()) s.erase(i);
    }

    void update(T x) {
        k += x;
    }

    T min() {
        return *s.begin() - k;
    }
};
