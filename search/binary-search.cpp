template <typename F = function<bool(const int &)>>
int binary_search(int low, int high, F check, bool first) {
    int answer = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (check(mid)) {
            answer = mid;
            if (first) high = mid - 1;
            else low = mid + 1;
        } else {
            if (first) low = mid + 1;
            else high = mid - 1;
        }
    }
    return answer;
}

template <typename F = function<bool(const float &)>>
float binary_search(float low, float high, F check, bool first, float eps = 1e-6) {
    float answer = -1;
    while (high - low > eps) {
        float mid = low + (high - low) / 2;

        if (check(mid)) {
            answer = mid;
            if (first) high = mid;
            else low = mid;
        } else {
            if (first) low = mid;
            else high = mid;
        }
    }
    return answer;
}
