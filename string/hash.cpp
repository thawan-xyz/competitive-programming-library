struct hash {
    static const long p1 = 41, p2 = 53;
    static const long m1 = 1e9 + 7, m2 = 1e9 + 9;
    array<long> hash1, hash2;
    array<long> pow1, pow2;
    
    hash(int n, str &s): hash1(n + 1), hash2(n + 1), pow1(n + 1, 1), pow2(n + 1, 1) {
        for (int i = 1; i <= n; ++i) {
            hash1[i] = (p1 * hash1[i - 1] + s[i - 1]) % m1;
            hash2[i] = (p2 * hash2[i - 1] + s[i - 1]) % m2;
            
            pow1[i] = (p1 * pow1[i - 1]) % m1;
            pow2[i] = (p2 * pow2[i - 1]) % m2;
        }
    }
    
    pair<long, long> range(int i, int j) {
        int length = j - i + 1;
        
        long range1 = hash1[j + 1] - (hash1[i] * pow1[length]) % m1;
        range1 %= m1; if (range1 < 0) range1 += m1;
        long range2 = hash2[j + 1] - (hash2[i] * pow2[length]) % m2;
        range2 %= m2; if (range2 < 0) range2 += m2;
        
        return {range1, range2};
    }
};
