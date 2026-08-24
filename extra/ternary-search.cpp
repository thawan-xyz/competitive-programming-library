int ternary_search(int low, int high, bool is_max) {
    while (high - low >= 3) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;

        if (is_max == (fun(mid1) < fun(mid2))) low = mid1;
        else high = mid2;
    }

    int ans = low;
    for (int i = low + 1; i <= high; ++i) if (is_max == (fun(ans) < fun(i))) ans = i;
    return ans;
}

float ternary_search(float low, float high, bool is_max) {
    for (int itr = 1; itr <= 100; ++itr) {
        float mid1 = low + (high - low) / 3.0;
        float mid2 = high - (high - low) / 3.0;

        if (is_max == (fun(mid1) < fun(mid2))) low = mid1;
        else high = mid2;
    }

    return (low + high) / 2.0;
}
