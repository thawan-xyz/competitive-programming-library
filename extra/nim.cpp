int nim(list<int> &piles, list<int> &moves) {
    int n = *max(piles.begin(), piles.end());
    list<int> grundy(n + 1);

    for (int i = 1; i <= n; ++i) {
        set<int> reach;
        for (int move : moves) if (move <= i) {
            reach.insert(grundy[i - move]);
        }

        int mex = 0;
        while (reach.contains(mex)) mex++;
        grundy[i] = mex;
    }

    int x = 0;
    for (int pile : piles) {
        x ^= grundy[pile];
    }
    return x;
}
