#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

struct custom_hash {
    size_t operator()(size_t x) const {
        static const size_t time = chrono::steady_clock::now().time_since_epoch().count();
        return (x + 0x9e3779b9) ^ time;
    }
};

template<typename T>
using hash_set = gp_hash_table<T, null_type, custom_hash>;

template<typename K, typename V>
using hash_map = gp_hash_table<K, V, custom_hash>;
