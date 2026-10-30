int ternary_search(int l, int r, bool is_max) {
    int a = l, b = r;
    while (l < r) {
        int m = l + (r - l) / 2;
        bool is_up = fun(m) < fun(m + 1);
        if (is_up == is_max) l = m + 1;
        else r = m;
    }
    for (int x : {a, b}) {
        bool is_up = fun(l) < fun(x);
        if (is_up == is_max) l = x;
    }
    return l;
}

float ternary_search(float l, float r, bool is_max) {
    for (int i = 0; i < 100; ++i) {
        float m1 = l + (r - l) / 3;
        float m2 = r - (r - l) / 3;
        bool is_up = fun(m1) < fun(m2);
        if (is_up == is_max) l = m1;
        else r = m2;
    }
    return (l + r) / 2;
}
