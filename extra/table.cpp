#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

const int random = chrono::high_resolution_clock::now().time_since_epoch().count();

struct rhash {
    int operator()(const int n) const {
        return n ^ random;
    }
};

template <typename T>
using uset = gp_hash_table<T, null_type, rhash>;

template <typename K, typename V>
using umap = gp_hash_table<K, V, rhash>;
