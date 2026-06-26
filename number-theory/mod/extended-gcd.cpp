// Extended GCD: finds coefficients x and y such that ax + by = gcd(a, b)
// Time: O(log(min(a, b))) | Space: O(log(min(a, b)))
// Note: returns [x0, y0] | all valid pairs are: x = x0 + k*(b/gcd) and y = y0 - k*(a/gcd)
pair<int, int> extended_gcd(int a, int b) {
    if (b == 0) return {1, 0};

    auto [x, y] = extended_gcd(b, a % b);
    return {y, x - (a / b) * y};
}
