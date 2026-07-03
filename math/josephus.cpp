// Josephus: finds survivor index eliminating every k-th person
// Time: O(N) | Space: O(N)
// Note: returns 0-based index
int josephus(int n, int k) {
    if (n == 1) return 0;
    return (josephus(n - 1, k) + k) % n;
}
