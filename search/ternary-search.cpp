int max_ternary_search() {
    int low = 0, high = n - 1;
    while (high - low > 3) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;
        if (f(mid1) < f(mid2)) {
            low = mid1;
        } else {
            high = mid2;
        }
    }
    int best = low;
    for (int i = low + 1; i <= high; ++i) {
        if (f(i) > f(best)) {
            best = i;
        }
    }
    return best;
}

float max_ternary_search() {
    float low = 0, high = n - 1;
    while (high - low > E) {
        float mid1 = low + (high - low) / 3;
        float mid2 = high - (high - low) / 3;
        if (f(mid1) < f(mid2)) {
            low = mid1;
        } else {
            high = mid2;
        }
    }
    return (low + high) / 2;
}

int min_ternary_search() {
    int low = 0, high = n - 1;
    while (high - low > 3) {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;
        if (f(mid1) > f(mid2)) {
            low = mid1;
        } else {
            high = mid2;
        }
    }
    int best = low;
    for (int i = low + 1; i <= high; ++i) {
        if (f(i) < f(best)) {
            best = i;
        }
    }
    return best;
}

float min_ternary_search() {
    float low = 0, high = n - 1;
    while (high - low > E) {
        float mid1 = low + (high - low) / 3;
        float mid2 = high - (high - low) / 3;
        if (f(mid1) > f(mid2)) {
            low = mid1;
        } else {
            high = mid2;
        }
    }
    return (low + high) / 2;
}
