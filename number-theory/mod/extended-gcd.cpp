pair<int, int> extended_gcd(int a, int b) {
    if (b == 0) return {1, 0};

    auto [x, y] = extended_gcd(b, a % b);
    return {y, x - (a / b) * y};
}
