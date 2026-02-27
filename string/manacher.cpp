string pre_process(string &s) {
    string t = "#";
    for (char &c : s) {
        t.push_back(c);
        t.push_back('#');
    }
    return t;
}

vector<int> manacher(string &s) {
    string t = '^' + pre_process(s) + '$';
    int n = t.length();

    vector<int> p(n);
    int c = 0, r = 0;
    for (int i = 1; i < n - 1; i++) {
        int j = 2 * c - i;
        if (i < r) {
            p[i] = min(r - i, p[j]);
        }
        while (t[i + (p[i] + 1)] == t[i - (p[i] + 1)]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            c = i;
            r = i + p[i];
        }
    }
    return p;
}

string longest_palindrome(string &s) {
    vector<int> p = manacher(s);
    int n = p.size();

    int k = 0, l = 0;
    for (int i = 1; i < n - 1; i++) {
        if (p[i] > l) {
            l = p[i];
            k = (i - l) / 2;
        }
    }
    return s.substr(k, l);
}

int count_palindromes(string &s) {
    vector<int> p = manacher(s);
    int n = p.size();

    int total = 0;
    for (int i = 1; i < n - 1; ++i) {
        total += (p[i] + 1) / 2;
    }
    return total;
}
