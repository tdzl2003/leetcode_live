# 题目地址：

https://atcoder.jp/contests/dp

# A - Frog 1

只能跳到 $i+1$ 和 $i+2$，反过来想就是只能从 $i-1$ 和 $i-2$ 跳过来，没什么特别思路，$O(N)$解决。

$$
DP[i] = min(DP[i-1]+|H[i-1]-H[i]|, DP[i-2]+|H[i-2]-H[i]|)
$$

[代码](https://atcoder.jp/contests/dp/submissions/34519975)

# B - Frog 2

可以跳到 $i+1$ 到 $i+k$ 了。反过来想从$i-1$到$i-k$范围，要求的是

$$
DP[i] = min(DP[j] + |H[j]-H[i]|)
$$

这个绝对值拆成两个部分，$H[j]<H[i]$ 和 $H[j]\ge H[i]$，就可以分别变形：

$$
DP[i] = \begin{cases}
min(DP[j] + H[j]) - H[i] & H[j] \ge H[i] \\
min(DP[j] - H[j]) + H[i] & H[j] < H[i]
\end{cases}
$$

因为$H[i]$的范围有限，所以其实就是针对高度的范围 min query，这里可以使用线段树解决。

复杂的地方在于相同高度可能有多个值，维护需要另外用一个 multimap

> 实际上$Nlg(H)+Nlg(K)$没比暴力$NK$好多少

[代码](https://atcoder.jp/contests/dp/submissions/34521005)

# C - Vacation

普通$O(N)$ DP，没有什么特别思路

$$
DP[i][0] = max(DP[i-1][1], DP[i-1][2]) + A[i][0]
$$

[代码](https://atcoder.jp/contests/dp/submissions/34522230)

# D - Knapsack 1

标准背包，$O(N*W)$ 过。注意看范围要用 int64 了。

状态空间，第一维表示只取 1..i 中的物体，第二维表示当前总重量。

$$
DP[i][j] = max(DP[i-1][j], DP[i-1][j-w[i]] + v[i])
$$

我的实现里用了 DP[0][i] = 0 的假设，也就是可以一开始装一个任意重量但没有分值的东西，这样最后只需要取 DP[N][w]就行了。
另外用从高到低的顺序计算来替代滚动数组

[代码](https://atcoder.jp/contests/dp/submissions/34523228)

# E - Knapsack 2

重量范围巨大的背包，但价值范围很低，因此只需要反过来思考：
只取 1..i，要取到指定的 value，最少需要多少 weight

这题告诉我们，有些情况下状态和数值是可以换过来用的。

$$
DP[i][j] = min(DP[i-1][j], DP[i-1][j-v[i]] + w[i])
$$

[代码](https://atcoder.jp/contests/dp/submissions/34523444)

## F - LCS

经典 LCS，但要求具体的 LCS 内容

$$
DP[i][j] = \begin{cases}
max(DP[i-1][j], DP[i][j-1]) & s[i-1] \ne s[j-1] \\
max(DP[i-1][j], DP[i][j-1], DP[i-1][j-1]+1) & s[i-1] = s[j-1]
\end{cases}
$$

注意可以证明

$$
DP[i-1][j]\le DP[i-1][j-1]+1 \\
DP[i][j-1]\le DP[i-1][j-1]+1
$$

所以递推可以简化为：

$$
DP[i][j] = \begin{cases}
max(DP[i-1][j], DP[i][j-1]) & s[i-1] \ne s[j-1] \\
DP[i-1][j-1]+1 & s[i-1] = s[j-1]
\end{cases}
$$

接下来的考察点就是通过 DP 数组追溯真正的解。解法就是当$s[i]\ne s[j]$时，观察 $DP[i-1][j]$和$DP[i][j-1]$哪个更大即可。

另外 LCS 还有[基于位运算的优化](https://www.cnblogs.com/-Wallace-/p/bit-lcs.html)，思路是把 DP 函数转化为差分数组，然后可以用位运算稍微加速一些。但即使用这种思路，也仍然得记录下每一行才能正确的找到解，并且在逆推时还要计数来求出 DP[i][j]，对这题好处并不大。

> 差分数组的前缀和就是 DP 数组，实际表达的是 s 的前缀和 t 的 LCS 长度，但是这个 LCS 未必是 s 和 t 的 LCS 的前缀 \
> 如 arbc 和 abcr， DP[2][4] = 2，表达'ar'这个前缀，但是整体的 LCS 是 'abc'

[代码](https://atcoder.jp/contests/dp/submissions/34525664)

# G - Longest Path

DAG 图上做 DP，结合拓扑排序

$$
DP[i] = max(pred[j]) + 1
$$

DAG 需要出边的临接表，并记录入边数量。为了方便，这里可以不一次求好 $DP[i]$，而是在遍历前驱点的时候，顺带更新 $DP[i]$。每个点被遍历到时，其前驱点都已经完成遍历，所以$DP[i]$也已经确定了。这样就不用记录两个临接表了。

[代码](https://atcoder.jp/contests/dp/submissions/34526356)

# H - Grid 1

输入是 N\*M 规模的那么就是朴素的递推（也被叫做 DP 但实际上不涉及最优化决策问题）

[代码](https://atcoder.jp/contests/dp/submissions/34526732)
