const int g = 3;
const int mod = 998244353;
const int max_len = 1 << 20;

array<int, max_len / 2> root, inv_root;

void roots() {
    root[0] = 1;
    inv_root[0] = 1;

    int ang = mpow(g, (mod - 1) / max_len);
    int inv_ang = mpow(ang, mod - 2);

    int half = max_len / 2;
    for (int i = 1; i < half; ++i) {
        root[i] = (ang * root[i - 1]) % mod;
        inv_root[i] = (inv_ang * inv_root[i - 1]) % mod;
    }
}

void ntt(vector<int> &p, bool inv) {
    int n = p.size();
    if (not inv) {
        for (int len = n; len >= 2; len /= 2) {
            int half = len / 2;
            int step = max_len / len;
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < half; ++j) {
                    int w = root[step * j];
                    int x = p[i + j];
                    int y = p[i + j + half];
                    p[i + j] = (x + y) % mod;
                    p[i + j + half] = (((x - y + mod) % mod) * w) % mod;
                }
            }
        }
    } else {
        for (int len = 2; len <= n; len *= 2) {
            int half = len / 2;
            int step = max_len / len;
            for (int i = 0; i < n; i += len) {
                for (int j = 0; j < half; ++j) {
                    int w = inv_root[step * j];
                    int x = p[i + j];
                    int y = (p[i + j + half] * w) % mod;
                    p[i + j] = (x + y) % mod;
                    p[i + j + half] = (x - y + mod) % mod;
                }
            }
        }
        int inv_n = mpow(n, mod - 2);
        for (int &x : p) x = (x * inv_n) % mod;
    }
}

vector<int> convolution(vector<int> a, vector<int> b) {
    int n = a.size() + b.size() - 1;
    int m = 1;
    while (m < n) m *= 2;

    a.resize(m);
    b.resize(m);
    ntt(a, false);
    ntt(b, false);

    for (int i = 0; i < m; ++i) a[i] = (a[i] * b[i]) % mod;
    ntt(a, true);
    a.resize(n);

    return a;
}
