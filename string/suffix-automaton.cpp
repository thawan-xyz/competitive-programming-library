struct suffix_automaton {
    struct node {
        int len = 0, link = 0;
        int pos = -1, cnt = 0;
        array<int, 26> next = {};
    };

    int prev;
    vector<node> st;

    suffix_automaton(): prev(1), st(2) {}

    void extend(char c) {
        int idx = c - 'a';
        int curr = st.size();
        int ptr = prev;

        st.emplace_back();
        st[curr].len = st[prev].len + 1;
        st[curr].pos = st[curr].len - 1;
        st[curr].cnt = 1;
        prev = curr;

        while (ptr and (not st[ptr].next[idx])) {
            st[ptr].next[idx] = curr;
            ptr = st[ptr].link;
        }

        if (not ptr) {
            st[curr].link = 1;
            return;
        }

        int qtr = st[ptr].next[idx];
        if (st[ptr].len + 1 == st[qtr].len) {
            st[curr].link = qtr;
            return;
        }

        int clone = st.size();
        st.push_back(st[qtr]);
        st[clone].len = st[ptr].len + 1;
        st[clone].cnt = 0;
    
        while (ptr and st[ptr].next[idx] == qtr) {
            st[ptr].next[idx] = clone;
            ptr = st[ptr].link;
        }

        st[curr].link = st[qtr].link = clone;
    }
};
