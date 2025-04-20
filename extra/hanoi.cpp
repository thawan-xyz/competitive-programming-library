void hanoi(int n, char l, char m, char r) {
    if (n == 0) return;
    hanoi(n - 1, l, r, m);
    write << "Move disk " << n << " from " << l << " to " << r << endl;
    hanoi(n - 1, m, l, r);
}
