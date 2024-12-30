#include <bits/stdc++.h>
#define array vector
#define read cin
#define str string
#define write cout
#define endl '\n'
using namespace std;

/* author: Thawan Silva, 2024-12-14
 * math: Prime Number Generator
 * url: https://github.com/thawan-xyz */

bool prime(int n) {
    if (n == 1 or n == 4) {
        return false;
    } else if (n <= 5) {
        return true;
    }

    for (int i : {2, 3, 5}) {
        if (n % i == 0) {
            return false;
        }
    }

    int l = sqrt(n) + 1;
    for (int i = 6; i <= l; i += 6) {
        if (n % (i - 1) == 0 or n % (i + 1) == 0) {
            return false;
        }
    }
    return true;
}
