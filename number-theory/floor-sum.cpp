// Floor Sum: calculates sum{i=0}^{n-1} floor((a * i + b) / m)
// Time: O(log m) | Space: O(1)
// Note: operates similarly to the euclidean algorithm | requires n >= 0, m >= 1, a >= 0, b >= 0
int floor_sum(int n, int m, int a, int b) {
    int s = 0;
    while (true) {
        if (a >= m) {
            s += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            s += n * (b / m);
            b %= m;
        }

        int y_max = a * n + b;
        if (y_max < m) break;

        y_max /= m;
        int x_max = y_max * m - b;

        s += (n - (x_max + a - 1) / a) * y_max;
        b = (a - x_max % a) % a;

        int m_next = a;
        a = m;
        m = m_next;
        n = y_max;
    }
    return s;
}
