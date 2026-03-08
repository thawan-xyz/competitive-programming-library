struct suffix_automaton {
    struct node {
        int len;
        int link;
        array<int, 26> next;

        node(int len): len(len) {
            link = -1;
            next.fill(-1);
        }
    };

    vector<node> states;
    int last;

    suffix_automaton(int n = 1) {
        states.reserve(2 * n);
        states.emplace_back(0);
        last = 0;
    }

    void extend(char c) {
        int curr = states.size();
        states.emplace_back(states[last].len + 1);
        int p = last;
        while (p != -1 and states[p].next[c - 'a'] == -1) {
            states[p].next[c - 'a'] = curr;
            p = states[p].link;
        }
        if (p == -1) {
            states[curr].link = 0;
        } else {
            int q = states[p].next[c - 'a'];
            if (states[q].len == states[p].len + 1) {
                states[curr].link = q;
            } else {
                int clone = states.size();
                states.push_back(states[q]);
                states[clone].len = states[p].len + 1;
                while (p != -1 and states[p].next[c - 'a'] == q) {
                    states[p].next[c - 'a'] = clone;
                    p = states[p].link;
                }
                states[q].link = clone;
                states[curr].link = clone;
            }
        }
        last = curr;
    }
};
