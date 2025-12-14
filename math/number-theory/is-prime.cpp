bool is_prime(int n) {
    if (n == 2 or n == 3) return true;
    if (n <= 1 or n % 2 == 0 or n % 3 == 0) return false;

    int s = sqrt(n);
    for (int i = 5; i <= s; i += 6) {
        if (n % i == 0 or n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}
