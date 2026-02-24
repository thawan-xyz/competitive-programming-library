struct offset_array {
    int l;
    list<int> a;

    offset_array(int l, int r, int x = 0): l(l), a((r - l) + 1, x) {}

    int &operator[](int i) {
        return a[i - l];
    }

    const int &operator[](int i) const {
        return a[i - l];
    }
};
