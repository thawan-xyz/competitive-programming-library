struct link_cut_tree {
    splay_tree st;

    void init(vector<int> &v) {
        st.init();
        for (int i = 1; i < v.size(); ++i) {
            st.t.emplace_back();
            st.t.back().init(v[i]);
        }
    }

    int access(int a) {
        int p = 0;
        for (int c = a; c != 0; c = st.t[c].p) {
            st.splay(c, 0);
            st.t[c].c[1] = p;
            st.pull(c);
            p = c;
        }
        st.splay(a, 0);
        return p;
    }

    void make_root(int a) {
        access(a);
        st.flip(a);
    }

    int find_root(int a) {
        access(a);
        while (st.t[a].c[0] != 0) {
            st.push(a);
            a = st.t[a].c[0];
        }
        st.splay(a, 0);
        return a;
    }

    void link(int a, int b) {
        make_root(a);
        if (find_root(b) != a) {
            st.t[a].p = b;
        }
    }

    void cut(int a, int b) {
        make_root(a);
        access(b);
        if (st.t[b].c[0] == a and st.t[a].c[1] == 0) {
            st.t[b].c[0] = 0;
            st.t[a].p = 0;
            st.pull(b);
        }
    }

    int lca(int a, int b) {
        if (find_root(a) != find_root(b)) return 0;
        access(a);
        return access(b);
    }

    void update(int a, int v) {
        st.splay(a, 0);
        st.t[a].val += v;
        st.pull(a);
    }

    int query(int a, int b) {
        make_root(a);
        access(b);
        return st.t[b].sum;
    }
};
