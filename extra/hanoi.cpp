void hanoi(int n, char l, char m, char r) {
    if (n == 0) return;
    hanoi(n - 1, l, r, m);
    print << "Move disk " << n << " from " << l << " to " << r << '\n';
    hanoi(n - 1, m, l, r);
}
