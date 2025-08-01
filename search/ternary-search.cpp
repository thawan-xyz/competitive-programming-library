template <typename F = function<int(const int &)>>
int ternary_search(int low, int high, F value, bool max) {
    while (high - low > 3) {
        int mid_low = low + (high - low) / 3;
        int mid_high = high - (high - low) / 3;

        if (max == (value(mid_low) > value(mid_high))) {
            high = mid_high;
        } else {
            low = mid_low;
        }
    }

    int answer = low;
    for (int i = low + 1; i <= high; ++i) {
        if (max == (value(i) > value(answer))) {
            answer = i;
        }
    }
    return answer;
}

template <typename F = function<float(const float &)>>
float ternary_search(float low, float high, F value, bool max, float eps = 1e-6) {
    while (high - low > eps) {
        float mid_low = low + (high - low) / 3;
        float mid_high = high - (high - low) / 3;

        if (max == (value(mid_low) > value(mid_high))) {
            high = mid_high;
        } else {
            low = mid_low;
        }
    }
    return (low + high) / 2;
}
