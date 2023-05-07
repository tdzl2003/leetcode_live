#include <vector>

struct DP {
    int x;
    DP(int x = 0) :x(x) {}
    DP operator+(const DP& a) const {
        return DP(x | a.x);
    }
    DP addRoot() const {
        return DP(!x);
    }
};


template<typename DP>
struct Rerooting {
    int n;
    std::vector<std::vector<int>> to;
    std::vector<std::vector<DP>> dp;
    std::vector<DP> ans;
    Rerooting(int n = 0) :n(n), to(n), dp(n), ans(n) {}
    void addEdge(int a, int b) {
        to[a].push_back(b);
        to[b].push_back(a);
    }
    void init() {
        dfs(0);
        bfs(0);
    }

    DP dfs(int v, int p = -1) {
        DP dpSum;
        dp[v] = std::vector<DP>(to[v].size());
        for (int i = 0; i < to[v].size(); i++) {
            int u = to[v][i];
            if (u == p) continue;
            dp[v][i] = dfs(u, v);
            dpSum = dpSum + dp[v][i];
        }
        return dpSum.addRoot(v, p);
    }
    void bfs(int v, const DP& dpP = DP(), int p = -1) {
        int deg = to[v].size();
        for (int i = 0; i < deg; ++i) {
            if (to[v][i] == p) dp[v][i] = dpP;
        }

        std::vector<DP> dpSumL(deg + 1);
        for (int i = 0; i < deg; i++) dpSumL[i + 1] = dpSumL[i] + dp[v][i];
        std::vector<DP> dpSumR(deg + 1);
        for (int i = deg - 1; i >= 0; --i)
            dpSumR[i] = dpSumR[i + 1] + dp[v][i];
        ans[v] = dpSumL[deg].addRoot(v, -1);

        for (int i = 0; i < deg; i++) {
            int u = to[v][i];
            if (u == p) continue;
            DP d = dpSumL[i] + dpSumR[i + 1];
            bfs(u, d.addRoot(v, u), v);
        }
    }
};


struct DP {
    mint val;
};

template<typename DP>
struct Rerooting {
    int N;
    vector<vector<int>> edges;
    vector<int> parents;
    vector<vector<int>> children;

    Rerooting(int n) : N(n) {
        edges.resize(n);
        parents.resize(n);
        children.resize(n);
    }

    addEdge(int f, int t) {
        f--; t--;
        edges[f].push_back(t);
        edges[t].push_back(f);
    }
};


// 下面的是非递归版本，还未完成。




#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <math.h>
#include <string.h>
#include <array>
#include <atcoder/all>

using namespace atcoder;
using namespace std;
typedef long long LL;

#ifndef ONLINE_JUDGE
#include <conio.h>
class __auto_getch {
public:
    ~__auto_getch() {
        _getch();
    }
} __auto_getch_instance;
#endif

using mint = atcoder::dynamic_modint<0>;


struct DP {
    mint val;
    DP() :val(0) {};
    DP(mint _val) :val(_val) {};
    DP operator +(DP other) {
        return DP(val * other.val);
    }
    void addRoot() {
        this->val++;
    }
};

template<typename DP = int>
struct Rerooting {
    int N;
    vector<vector<int>> edges;
    vector<int> parents;
    vector<vector<int>> children;
    vector<int> visitOrder, reverseOrder;

    vector<DP> f, g, res;

    Rerooting(int n) : N(n) {
        edges.resize(n);
        parents.resize(n);
        children.resize(n);
    }

    void addEdge(int f, int t) {
        edges[f].push_back(t);
        edges[t].push_back(f);
    }

    void solveVisitOrder() {
        parents.resize(N);
        children.resize(N);

        stack<int> s;
        vector<int> visited;
        visited.resize(N);
        s.push(0); parents[0] = -1;

        while (s.size() > 0) {
            int r = s.top();
            visited[r] = true;
            s.pop();
            visitOrder.push_back(r);
            for (auto v : edges[r]) {
                if (!visited[v]) {
                    children[r].push_back(v);
                    parents[v] = r;
                    s.push(v);
                }
            }
        }

        reverseOrder = visitOrder;
        std::reverse(reverseOrder.begin(), reverseOrder.end());
    }

    void solve() {
        solveVisitOrder();
        f.resize(N);
        g.resize(N);
        res.resize(N);

        {
            // leaf -> root visit, calc f(i)
            f.resize(N);
            for (auto i : reverseOrder) {
                for (auto v : children[i]) {
                    f[i] = f[i] + f[v];
                }
                f[i].addRoot();
            }
        }

        {
            // root -> leave visit, calc g(i)
            g.resize(N);
            for (auto i : visitOrder) {
                g[i].addRoot();
                res[i] = f[i] + g[i];
                auto& c = children[i];
                vector<DP> prefix, suffix;
                int m = c.size();
                prefix.resize(m + 1);
                prefix[0] = g[i];
                suffix.resize(m + 1);
                for (int j = 0; j < m; j++) {
                    prefix[j + 1] = prefix[j] + f[c[j]];
                    suffix[j + 1] = suffix[j] + f[c[m - j - 1]];
                }
                for (int j = 0; j < m; j++) {
                    g[c[j]] = g[i] + prefix[j] + suffix[m - j - 1];
                }
            }
        }
    }
};

int main()
{
    int N, M;
    scanf("%d%d", &N, &M);
    atcoder::dynamic_modint<0>::set_mod(M);

    Rerooting<DP> rr(N);

    for (int i = 1; i < N; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--; y--;
        rr.addEdge(x, y);
    }

    rr.solve();
    for (int i = 0; i < N; i++) {
        printf("%d\n", rr.res[i].val.val());
    }

    return 0;
}


