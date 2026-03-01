template <typename T>
ostream &operator<<(ostream &out, const vector<T> &a) {
    for (int i = 0; i < a.size(); ++i) {
        if (i != 0) out << ' ';
        out << a[i];
    }
    return out;
}
