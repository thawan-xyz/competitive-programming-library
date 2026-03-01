template <typename T>
struct offset {
    int l;
    vector<T> a;

    offset(int l, int r, T x = T()): l(l), a(r - l, x) {}

    T &operator[](int i) {
        return a[i - l];
    }

    const T &operator[](int i) const {
        return a[i - l];
    }
};
