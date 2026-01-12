struct venice_set {
    int k = 0;
    multiset<int> s;

    int size() {
        return s.size();
    }

    void insert(int x) {
        s.insert(x - k);
    }

    void remove(int x) {
        auto i = s.find(x - k);
        if (i != s.end()) s.erase(i);
    }

    void modify(int x) {
        k += x;
    }

    int min() {
        return *s.begin() + k;
    }
};
