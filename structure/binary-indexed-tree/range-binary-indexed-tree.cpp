struct range_bit {
    bit mul, sub;

    range_bit(int n): mul(n + 1), sub(n + 1) {}

    void update(int i, int j, int x) {
        mul.update(i, x);
        mul.update(j + 1, -x);

        sub.update(i, x * (i - 1));
        sub.update(j + 1, -x * j);
    }

    int prefix(int i) {
        return mul.prefix(i) * i - sub.prefix(i);
    }

    int query(int i, int j) {
        return prefix(j) - prefix(i - 1);
    }
};
