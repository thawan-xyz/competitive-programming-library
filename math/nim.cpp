bool nim(vector<int> &piles, vector<int> &moves) {
    int n = *max(piles.begin(), piles.end());
    vector<int> grundy(n + 1);

    for (int i = 1; i <= n; ++i) {
        set<int> reach;
        for (int move : moves) if (move <= i) {
            reach.insert(grundy[i - move]);
        }

        int mex = 0;
        while (reach.contains(mex)) mex++;
        grundy[i] = mex;
    }

    int answer = 0;
    for (int pile : piles) {
        answer ^= grundy[pile];
    }
    return answer != 0;
}

bool misere(vector<int> &piles, vector<int> &moves) {
    int n = *max(piles.begin(), piles.end());
    vector<int> grundy(n + 1);

    for (int i = 1; i <= n; ++i) {
        set<int> reach;
        for (int move : moves) if (move <= i) {
            reach.insert(grundy[i - move]);
        }

        int mex = 0;
        while (reach.contains(mex)) mex++;
        grundy[i] = mex;
    }

    bool all_one = true;
    int answer = 0;
    for (int pile : piles) {
        all_one &= grundy[pile] == 1;
        answer ^= grundy[pile];
    }
    return all_one ? (piles.size() & 1) == 0 : answer != 0;
}
