// Berlekamp-Massey: finds the shortest linear recurrence of a sequence
// Time: O(N^2) where N is sequence size | Space: O(N)
// Note: requires at least 2L terms to correctly find a recurrence of length L
vector<int> berlekamp_massey(const vector<int> &seq) {
    vector<int> old = {1}, curr = {1};
    int prev = 1, len = 0, shift = 1;
    for (int i = 0; i < seq.size(); ++i) {
        int delta = 0;
        for (int j = 0; j <= len; ++j) {
            delta = (delta + curr[j] * seq[i - j]) % mod;
        }
        if (delta == 0) {
            shift++;
            continue;
        } 
        vector<int> temp = curr;
        int mult = (mod - (delta * power(prev, mod - 2)) % mod) % mod;
        if (curr.size() <= old.size() + shift) {
            curr.resize(old.size() + shift + 1, 0);
        }
        for (int j = 0; j < old.size(); ++j) {
            curr[j + shift] = (curr[j + shift] + mult * old[j]) % mod;
        }
        if (2 * len <= i) {
            len = i + 1 - len;
            old = temp;
            prev = delta;
            shift = 1;
        } else {
            shift++;
        }
    }
    vector<int> coef(len);
    for (int i = 1; i <= len; ++i) {
        coef[i - 1] = (mod - curr[i]) % mod;
    }
    return coef;
}
