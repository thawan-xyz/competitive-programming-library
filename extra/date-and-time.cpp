// Date and Time: dates as day, month, year and clock times as seconds
// Time: O(1) per operation | Space: O(1)
string pad(int x, int w) {
    string s = to_string(x);
    while (s.size() < w) s = "0" + s;
    return s;
}

// "hh:mm:ss" -> seconds since 00:00:00
int to_seconds(const string &t) {
    int h, m, s;
    char c;
    stringstream(t) >> h >> c >> m >> c >> s;
    return h * 3600 + m * 60 + s;
}

// seconds -> "hh:mm:ss" (to_clock((x % 86400 + 86400) % 86400) wraps around midnight)
string to_clock(int x) {
    return pad(x / 3600, 2) + ":" + pad(x / 60 % 60, 2) + ":" + pad(x % 60, 2);
}

// "dd/mm/yyyy" -> {d, m, y}
array<int, 3> parse(const string &t) {
    int d, m, y;
    char c;
    stringstream(t) >> d >> c >> m >> c >> y;
    return {d, m, y};
}

// [d, m, y] -> "dd/mm/yyyy"
string show(int d, int m, int y) {
    return pad(d, 2) + "/" + pad(m, 2) + "/" + pad(y, 4);
}

bool is_leap(int y) {
    return (y % 4 == 0 and y % 100 != 0) or y % 400 == 0;
}

int month_days(int m, int y) {
    const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return days[m - 1] + (m == 2 and is_leap(y));
}

// number of the day d/m/y, counting from 01/01/0001 = 1
int to_days(int d, int m, int y) {
    const int before[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int p = y - 1;
    return p * 365 + p / 4 - p / 100 + p / 400 + before[m - 1] + (m > 2 and is_leap(y)) + d;
}

// [d, m, y] of the day number z, inverse of to_days
array<int, 3> from_days(int z) {
    int y = z * 400 / 146097 + 1;
    while (to_days(1, 1, y) > z) y--;
    while (to_days(1, 1, y + 1) <= z) y++;
    z -= to_days(1, 1, y) - 1;
    int m = 1;
    while (z > month_days(m, y)) z -= month_days(m++, y);
    return {z, m, y};
}

int weekday(int d, int m, int y) {
    return (to_days(d, m, y) - 1) % 7;
}

array<int, 3> add_days(int d, int m, int y, int k) {
    return from_days(to_days(d, m, y) + k);
}

int days_between(int d1, int m1, int y1, int d2, int m2, int y2) {
    return to_days(d2, m2, y2) - to_days(d1, m1, y1);
}

array<int, 3> add_months(int d, int m, int y, int k) {
    int t = y * 12 + m - 1 + k;
    y = t / 12, m = t % 12 + 1;
    return {min(d, month_days(m, y)), m, y};
}
