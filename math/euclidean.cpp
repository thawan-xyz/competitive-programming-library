tuple<int, int, int> egcd(int a, int b) {
    if (b == 0) return {a, 1, 0};

    auto [g, x, y] = egcd(b, a % b);
    return {g, y, x - (a / b) * y};
}
