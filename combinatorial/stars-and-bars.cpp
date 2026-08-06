// Stars and Bars: number of ways to put n identical items into k distinct bins
// Time: O(1) | Space: O(1)
// Note: requires C(n, k) function | counts non-negative integer solutions to x1 + ... + xk = n
int stars_and_bars(int n, int k) {
    if (n < 0 or k < 0) return 0;
    if (k == 0) return n == 0;
    return C(n + k - 1, k - 1);
}
