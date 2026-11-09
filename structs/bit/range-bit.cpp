struct range_bit {
    bit m, s;

    range_bit(int n): m(n + 1), s(n + 1) {}

    void update(int i, int j, int x) {
        m.update(i, x);
        m.update(j + 1, -x);
        s.update(i, x * (i - 1));
        s.update(j + 1, -x * j);
    }

    int prefix(int i) {
        return i * m.prefix(i) - s.prefix(i);
    }

    int query(int i, int j) {
        return prefix(j) - prefix(i - 1);
    }
};
