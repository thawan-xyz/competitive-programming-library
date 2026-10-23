// Floor Sum: calculates sum_{i=0}^{n-1} floor((a * i + b) / c)
// Time: O(log c) | Space: O(log c)
// Note: requires n >= 0 and c >= 1
int floor_sum(int n, int a, int b, int c) {
    if (n == 0) return 0;
    int x = (a % c + c) % c, y = (b % c + c) % c;
    int r = n * (n - 1) / 2 * ((a - x) / c) + n * ((b - y) / c);
    int t = x * n + y;
    return r + floor_sum(t / c, c, t % c, x);
}

// Floor Sum Range: calculates sum_{i=l}^{r-1} floor((a * i + b) / c)
// Time: O(log c) | Space: O(log c)
// Note: requires l < r and c >= 1
int floor_sum_range(int l, int r, int a, int b, int c) {
    return floor_sum(r - l, a, a * l + b, c);
}
