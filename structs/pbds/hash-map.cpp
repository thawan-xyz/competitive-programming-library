#include <ext/pb_ds/assoc_container.hpp>
#define uint unsigned long long
using namespace __gnu_pbds;

struct safe_hash {
    static uint mix(uint x) {
        static const uint seed = chrono::steady_clock::now().time_since_epoch().count();
        x += seed;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    uint operator()(const auto &x) const {
        uint h = 0;
        if constexpr (is_same_v<decay_t<decltype(x)>, string>) {
            for (int i = 0; i < x.size(); i += 8) {
                uint w = 0;
                memcpy(&w, x.data() + i, min<int>(8, x.size() - i));
                h = mix(h + w);
            }
        } else if constexpr (requires { x.begin(); }) {
            for (auto &y : x) h = mix(h + (*this)(y));
        } else if constexpr (requires { get<0>(x); }) {
            apply([&](auto &...y) { ((h = mix(h + (*this)(y))), ...); }, x);
        } else {
            h = mix(x);
        }
        return h;
    }
};

template <typename K, typename V> using hash_map = gp_hash_table<K, V, safe_hash>;
