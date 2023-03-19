struct Tree {
    int n, k;
    vector<vector<int>> children;

    Tree(int n_ = 0): n(n_), k(max(1, ceil_pow2(n_))), children(n_) {}

    vector<int> h;
    vector<vector<int>> up;

private:
    void prela_dfs(int v, int p, int d) {
        h[v] = d;
        up[v][0] = p;
        for (int j = 1; j < k; j++) {
            up[v][j] = up[up[v][j - 1]][j - 1];
        }
        for (auto u : children[v]) {
            prela_dfs(u, v, d + 1);
        }
    }
public:
    /* 倍增预处理2^k祖先节点，用于LCA等 */
    void prela() {
        h.resize(n);
        up.resize(n, vector<int>(K));
        prela_dfs(0, 0, 0);
    }

    /* 获取x次祖先节点 */
    int la(int v, int x) {
        for (int j = 0; j < k; j++) {
            if (x >> j & 1) {
                v = up[v][j];
            }
        }
        return v;
    }

    /* 获取v和u的最近公共祖先 */
    int lca(int v, int u) {
        if (h[v] > h[u]) {
            swap(v, u);
        }
        u = la(u, h[u] - h[v]);
        if (v == u) {
            return v;
        }
        for (int j = k - 1; j >= 0; j--) {
            if (up[v][j] != up[u][j]) {
                v = up[v][j], u = up[u][j];
            }
        }
        return up[v][0];
    }

};