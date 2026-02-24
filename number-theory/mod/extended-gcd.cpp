tuple<int, int, int> extended_gcd(int a, int b) {
    if (b == 0) return {a, 1, 0};

    auto [g, x, y] = extended_gcd(b, a % b);
    return {g, y, x - (a / b) * y};
}
