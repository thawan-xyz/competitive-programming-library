#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct random {
    const int seed = chrono::steady_clock::now().time_since_epoch().count();

    int operator()(int n) const {
        return n ^ seed;
    }
};

template <typename K, typename V>
using hash_table = gp_hash_table<K, V, random>;
