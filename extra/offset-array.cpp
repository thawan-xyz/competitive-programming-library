template <typename T>
struct offset_array {
    int l;
    list<T> a;

    offset_array(int l, int r, T x = T()): l(l), a(r - l, x) {}

    T &operator[](int i) {
        return a[i - l];
    }

    const T &operator[](int i) const {
        return a[i - l];
    }
};
