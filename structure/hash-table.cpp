#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct random_hash {
    const int random = chrono::high_resolution_clock::now().time_since_epoch().count();

    int operator()(const int n) const {
        return n ^ random;
    }
};

template <typename k, typename v>
using hash_table = gp_hash_table<k, v, random_hash>;
