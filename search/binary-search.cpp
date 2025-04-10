int left_binary_search(array<int> a) {
    int low = 0, high = a.size() - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        if (check(mid)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return check(low) ? low : -1;
}

int right_binary_search(array<int> a) {
    int low = 0, high = a.size() - 1;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    return check(low) ? low : -1;
}
