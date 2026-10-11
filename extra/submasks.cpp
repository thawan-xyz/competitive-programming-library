void submasks(int mask) {
    for (int submask = mask; submask > 0; submask = mask & (submask - 1)) {
        process(submask);
    }
    process(0);
}
