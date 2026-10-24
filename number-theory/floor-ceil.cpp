int floor(int x, int y) {
    return (x / y) - (((x ^ y) < 0) & x % y != 0);
}

int ceil(int x, int y) {
    return (x / y) + (((x ^ y) >= 0) & x % y != 0);
}
