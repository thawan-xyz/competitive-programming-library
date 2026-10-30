// Segmented Sieve: primes in [l, r], crossing out the multiples of the primes up to sqrt(r)
// Time: O((r - l) log log r + sqrt(r)) | Space: O(r - l + sqrt(r))
// Note: uses linear_sieve | is_prime[i - l] tells if i is prime
vector<int> segmented_sieve(int l, int r) {
    vector<int> primes = linear_sieve(sqrt(r));
    vector<bool> is_prime(r - l + 1, true);
    for (int p : primes) {
        for (int i = max(p * p, (l + p - 1) / p * p); i <= r; i += p) {
            is_prime[i - l] = false;
        }
    }
    primes.clear();
    for (int i = max<int>(2, l); i <= r; ++i) {
        if (is_prime[i - l]) primes.push_back(i);
    }
    return primes;
}
