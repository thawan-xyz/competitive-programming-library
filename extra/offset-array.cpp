template <typename T>
struct offset_array {
    int l;
    list<T> a;

    offset_array(int l, int r, T x = T()): l(l), a((r - l) + 1, x) {}

    int &operator[](int i) {
        return a[i - l];
    }

    const int &operator[](int i) const {
        return a[i - l];
    }
};
