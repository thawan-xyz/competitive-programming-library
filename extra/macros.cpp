#define read(...) ([&](auto&... args) {(cin >> ... >> args);}(__VA_ARGS__))
#define print(...) ([&](auto&&... args) {(cout << ... << args);}(__VA_ARGS__))
