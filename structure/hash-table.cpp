#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct random_hash {
    const int random = chrono::high_resolution_clock::now().time_since_epoch().count();

    int operator()(int n) const {
        return n ^ random;
    }
};

template <typename K, typename V>
using hash_table = gp_hash_table<K, V, random_hash>;
