/*
莫队算法：用于O(1)迭代的批量区段查询，可在 O(N*sqrt(Q)) 时间离线处理
需要提供状态维护类型 State，支持插入和删除一个下标。
暂时还没有支持区分是左侧插入删除还是右侧插入删除，等有需求了再迭代。
*/

struct State {
    void push(int i) {
    }
    void pop(int i) {
    }
    long long get() {
    }
};

template <typename RetType, typename State>
struct MoAlgo {
    struct MoQuery {
        int l, r;
        int idx;
    };

    State state;
    vector<MoQuery> queries;
    vector<RetType> ans;

    void addQuery(int l, int r) {
        queries.push_back({ l, r, (int)queries.size() });
    }

    void solve() {
        ans.resize(queries.size());

        int B = sqrt(queries.size());
        sort(queries.begin(), queries.end(), [this, B](const MoQuery& a, const MoQuery& b) {
            int al = a.l / B, bl = b.l / B;
            if (al != bl) {
                return al < bl;
            }
            return a.r < b.r;
        });


        int l = 0, r = 0;
        for (auto& v : queries) {
            while (r < v.r) {
                state.push(r++);
            }
            while (r > v.r) {
                state.pop(--r);
            }
            while (l > v.l) {
                state.push(--l);
            }
            while (l < v.l) {
                state.pop(l++);
            }
            ans[v.idx] = state.get();
        }
    }
};
