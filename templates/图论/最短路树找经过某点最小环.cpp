// source: https://atcoder.jp/contests/abc308/editorial/6718
// 修改处理inf问题
// 只需要换的长度可以删掉最后一段，直接返回mn

static const int inf = 1000000000;

pair<int, vector<int>> shortest_cycle(const vector<vector<int>>& G, int r) {
    int n = G.size();
    vector<int> dist(n, inf), p(n, -1), g(n);
    vector<bool> seen(n);
    dist[r] = 0;
    g[r] = r;
    // 构造最短路树
    for (int t = 0; t < n; t++) {
        int mn = inf + 1, pos = -1;
        for (int i = 0; i < n; i++) {
            if (!seen[i] and dist[i] < mn) {
                mn = dist[i];
                pos = i;
            }
        }
        assert(pos != -1);
        seen[pos] = true;
        for (int i = 0; i < n; i++) {
            if (dist[i] > dist[pos] + G[pos][i]) {
                dist[i] = dist[pos] + G[pos][i];
                p[i] = pos;
                g[i] = (pos == r ? i : g[pos]);
            }
        }
    }
    // 找最小环。
    int mn = inf;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i] == j or p[j] == i) continue;
            if (g[i] == g[j]) continue;
            mn = min(mn, dist[i] + dist[j] + G[i][j]);
        }
    }
    // 求具体路径。可以删掉这一段，直接返回mn来只求最小环长度。
    if (mn == inf) {
        return { mn, vector<int>() };
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i] == j or p[j] == i) continue;
            if (g[i] == g[j]) continue;
            if (mn != dist[i] + dist[j] + G[i][j]) continue;
            vector<int> res;
            int a = i, b = j;
            while (a != r) {
                res.push_back(a);
                a = p[a];
            }
            res.push_back(a);
            reverse(res.begin(), res.end());
            while (b != r) {
                res.push_back(b);
                b = p[b];
            }
            return { mn, res };
        }
    }
    assert(false);
}