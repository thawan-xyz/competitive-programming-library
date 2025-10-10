int nim(list<int> &piles, list<int> &moves) {
    int size = max(piles);
    list<int> grundy(size + 1);

    for (int i = 1; i <= size; ++i) {
        set<int> reach;
        for (int move : moves) if (move <= i) {
            reach.insert(grundy[i - move]);
        }

        int mex = 0;
        while (reach.contains(mex)) mex++;
        grundy[i] = mex;
    }

    int result = 0;
    for (int pile : piles) {
        result ^= grundy[pile];
    }
    return result;
}
