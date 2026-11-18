struct flat_index {
    vector<int> dim;
    int size = 1;

    flat_index(auto... d) {
        (dim.push_back(d), ...);
        for (int x : dim) size *= x;
    }

    int index(auto... x) {
        int id = 0, i = 0;
        ((id = id * dim[i++] + x), ...);
        return id;
    }

    vector<int> coord(int id) {
        vector<int> res(dim.size());
        for (int i = dim.size() - 1; i >= 0; --i) res[i] = id % dim[i], id /= dim[i];
        return res;
    }
};
