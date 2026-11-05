// Catalan (Ballot Theorem): number of grid paths from (0,0) to (l,r) staying x >= y at all times
// Time: O(1) | Space: O(1)
// Note: requires comb(n, k) | also counts valid parenthesis prefixes (l open, r close)
int catalan(int l, int r) {
    if ((l < 0 or r < 0) or l < r) return 0;
    return (comb(l + r, l) - comb(l + r, l + 1) + mod) % mod;
}
