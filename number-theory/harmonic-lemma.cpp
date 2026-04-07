// Harmonic Lemma: Quotient Blocks in a specific range [L, R]
// Time: O(sqrt(N)) | Space: O(1)
// Note: Iterates over ranges [I, J] inside [L, R] where floor(n / k) is exactly q
int harmonic_lemma(int n, int l, int r) {
    int s = 0;
    for (int i = l, j; i <= r; i = j + 1) {
        int q = n / i;
        if (q == 0) {
            j = r;
        } else {
            j = min(r, n / q);
        }
        s += q * (j - i + 1);
    }
    return s;
}
