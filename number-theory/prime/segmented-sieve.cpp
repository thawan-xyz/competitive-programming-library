list<int> segmented_sieve(int l, int r) {
    list<int> primes = linear_sieve(sqrt(r));
    offset_array<char> is_prime(l, r + 1, true);
    for (int p : primes) {
        for (int i = max(p * ((l + p - 1) / p), p * p); i <= r; i += p) {
            is_prime[i] = false;
        }
    }
    primes.clear();
    for (int i = max(2, l); i <= r; ++i) {
        if (is_prime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}
