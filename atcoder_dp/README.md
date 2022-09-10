# 题目地址：

https://atcoder.jp/contests/dp

这里只记录了一些我自己刷这套题时想到的细节和一些优化方法，还有很多更基础的知识点和更高级的玩法还是请移步[OIWiki](https://oiwiki.com/dp/)。

## 滚动数组

其实就是长度固定为 1 或 2 的滑动窗口。 DP 有多个维度时，往往只能选一个维度来滑动。

在特定情况下，可以用原地更新来取代滚动数组（如背包问题），但需要注意更新顺序。
具体可以详读[oiwiki 中对背包问题的解读](https://oiwiki.com/dp/knapsack/)

在另外一些特定情况下，滚动数组还可以表示为线性变换，从而用矩阵求解，后面会单独聊矩阵求解的话题。

## 边界处理

DP 有多个维度时，经常需要做边界处理，此时可以避免在递推函数上做判断，而去把范围外的值定义成运算的“幺元” $E$ (对运算 ×，和任意的 $X$ ，都满足 $X×E=X$ )

- 加法的幺元是 0
- 乘法的幺元是 1
- min 的幺元是 $∞$ ，实际编程中可以计算出一个上界来替代 $∞$
- max 的幺元是 $-∞$ ，如果答案确定为非负整数，可以用 0 作为幺元。

如果采用记忆化搜索的方式来实现，可以判断出界然后返回幺元；
如果采用数组递推的方式，往往可以用“出血”的方式来处理边界，就是在数组前后根据需要增加一个或多个单位的下标，其值直接初始化为幺元，而不被递推过程计算，但可以被递推过程取用。

## 从 DP 表获取最优解

决策类问题，从 DP 表中获取最优解，核心关键就在于 min/max 函数实际选择了哪个分支。

当存在分支时，找到和 min/max 函数结果一致的那个分支，就可以逆推出最优解。

## 记忆化搜索

虽然很多人用 map 或 hashmap 做记忆化搜索，但是这里存在不确定的额外开销。
如果用标记数组，许多时候能保持记忆化搜索的代码结构同时取得更好的性能。

> L - Deque 是一个例子

## 矩阵乘法

如果递推公式可以表达为常系数的线性递推式，并且向量宽度不太大，就可以用矩阵乘法快速求解。

有两种形式：

二维 DP 式

$$
f_{i,0} = k_{0,0}f_{i-1,0}+k_{0,1}f_{i-1,1}+....+k_{0,m}f_{i-1,m}
$$

$$
f_{i,1} = k_{1,0}f_{i-1,0}+k_{1,1}f_{i-1,1}+....+k_{1,m}f_{i-1,m}
$$

$$
...
$$

$$
f_{i,m} = k_{m,0}f_{i-1,0}+k_{m,1}f_{i-1,1}+....+k_{m,m}f_{i-1,m}
$$

可以表达为矩阵

$$
F_{i} = \begin{bmatrix}
f_{i,0} \\
f_{i,1} \\
... \\
f_{i,m}
\end{bmatrix}
$$

$$
B = \begin{bmatrix}
k_{0,0} & k_{0,1} & ... & k_{0,m} \\
k_{1,0} & k_{1,1} & ... & k_{1,m} \\
... & ... & ... & ... \\
k_{m,0} & k_{m,1} & ... & k_{m,m} \\
\end{bmatrix}
$$

$$
\begin{aligned}
F_{i} = & B × F_{i-1} \\
 = & B^{i} × F_{0}
\end{aligned}
$$

此时可以采用快速幂方法在 $O(lgn)$ 求出 $B^n$ 从而迅速求解 $F_{n}$

许多具有时间或下标维度的状态机上的计数或决策问题都可以转变成该方法的矩阵求解

> 例题：求长度为 n 的，恰好两次出现连续的 red 的组合总数

另一方面，一维线性递推式：

$$
f_{X} = k_1f_{X-1}+k_2f_{X-2}+...k_nf_{X-n}
$$

可以转换为二维递推式

$$
\begin{aligned}
f_{i, 0} = &  f_{i-1, 1} \\
f_{i, 1} = & f_{i-1, 2} \\
…&… \\
f_{i, m-1} = & f_{i-1, m} \\
f_{i, m} = & k_nf_{i-1, 0} + ... + k_2f_{i-1, m-1} + k_1f_{i-1,m}
\end{aligned}
$$

从而转变为矩阵

$$
\begin{bmatrix}
0 & 1 & 0 & 0 & ... & 0 \\
0 & 0 & 1 & 0 & ... & 0 \\
0 & 0 & 0 & 1 & ... & 0 \\
... & ... & ... & ... & ... & ... \\
0 & 0 & 0 & 0 & ... & 1 \\
k_m & k_{n-1} & k_{n-2} & k_{n-3} & ... & k_{1}
\end{bmatrix}
$$

的快速幂。

> 例题：斐波那契数列，或者台阶问题等。

注意，矩阵乘法不仅仅对于算术加法和乘法生效，对于任何两个符合分配率和结合律的操作＋和 × 都可以进行，如模加和模乘，异或和逻辑与

## 位运算压缩

如果 DP 函数的值只有 0 和 1 两种选项，可以尝试用位运算进行压缩。K - Stones 是个典型题目。

LCS 是另一个例子，但是更复杂一些，它利用的是 DP 函数的行差分函数只有 0 和 1 这个性质。

位运算压缩无法改变复杂度，但是可能可以成倍的甚至成 64 倍的加速计算过程。

## 压缩计算过程复杂度

很多例题，维度状态是无法压缩的，但是可以设法压缩计算过程中的复杂度，尤其是对于求区段和、求区段最小最大、计数等，方法包括且不限于：

- 连续计算中间状态
- 前缀和
- [单调队列/单调栈](https://oiwiki.com/dp/opt/monotonous-queue-stack/)
- 线段树/树状数组/ST 树
- [四边形不等式优化](https://oiwiki.com/dp/opt/quadrangle/)
- FFT 求卷积

# A - Frog 1

只能跳到 $i+1$ 和 $i+2$，反过来想就是只能从 $i-1$ 和 $i-2$ 跳过来，没什么特别思路， $O(N)$ 解决。

$$
DP[i] = min(DP[i-1]+|H[i-1]-H[i]|, DP[i-2]+|H[i-2]-H[i]|)
$$

[代码](https://atcoder.jp/contests/dp/submissions/34519975)

# B - Frog 2

可以跳到 $i+1$ 到 $i+k$ 了。反过来想从 $i-1$ 到 $i-k$ 范围，要求的是

$$
DP[i] = min(DP[j] + |H[j]-H[i]|)
$$

这个绝对值拆成两个部分， $H[j] \lt H[i]$ 和 $H[j]\ge H[i]$，就可以分别变形：

$$
DP[i] = \begin{cases}
min(DP[j] + H[j]) - H[i] & H[j] \ge H[i] \\
min(DP[j] - H[j]) + H[i] & H[j] \lt H[i]
\end{cases}
$$

因为 $H[i]$ 的范围有限，所以其实就是针对高度的范围 min query，这里可以使用线段树解决。

复杂的地方在于相同高度可能有多个值，维护需要另外用一个 multimap

> 实际上 $NlgH+NlgK$ 没比暴力 $NK$ 好多少

[代码](https://atcoder.jp/contests/dp/submissions/34521005)

# C - Vacation

普通 $O(N)$ DP，没有什么特别思路

$$
DP[i][0] = max(DP[i-1][1], DP[i-1][2]) + A[i][0]
$$

[代码](https://atcoder.jp/contests/dp/submissions/34522230)

# D - Knapsack 1

标准背包， $O(N*W)$ 过。注意看范围要用 int64 了。

状态空间，第一维表示只取 1..i 中的物体，第二维表示当前总重量。

$$
DP[i][j] = max(DP[i-1][j], DP[i-1][j-w[i]] + v[i])
$$

我的实现里用了 $DP[0][i] = 0$ 的假设，也就是可以一开始装一个任意重量但没有分值的东西，这样最后只需要取 $DP[N][w]$ 就行了。
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
\begin{align}
DP[i-1][j]\le & DP[i-1][j-1]+1 \\
DP[i][j-1]\le  &DP[i-1][j-1]+1
\end{align}
$$

所以递推可以简化为：

$$
DP[i][j] = \begin{cases}
max(DP[i-1][j], DP[i][j-1]) & s[i-1] \ne t[j-1] \\
DP[i-1][j-1]+1 & s[i-1] = t[j-1]
\end{cases}
$$

接下来的考察点就是通过 DP 数组追溯真正的解。解法就是当 $s[i]\ne s[j]$ 时，观察 $DP[i-1][j]$ 和 $DP[i][j-1]$ 哪个更大即可。

[普通实现代码](https://atcoder.jp/contests/dp/submissions/34525664)

另外 LCS 还有[基于位运算的优化](https://www.cnblogs.com/-Wallace-/p/bit-lcs.html)，思路是把 DP 函数转化为差分数组，然后可以用位运算稍微加速一些。但即使用这种思路，也仍然得记录下每一行才能正确的找到解。

> 差分数组的前缀和就是 DP 数组，实际表达的是 s 的前缀和 t 的 LCS 长度，但是这个 LCS 未必是 s 和 t 的 LCS 的前缀 \
> 如 abcr 和 arbc， DP[4][2] = 2，表达 LCS(abcr,ar)=ar，但是 LCS(abcr,arbc) = abc

但是可以看出，当 $s[i-1] \ne t[j-1]$ 时，如果 $M[i][j] = 0$ ，那么有 $DP[i][j] = DP[i][j-1]$ ，因此一定可以选择向左移动。否则，必须选择向上移动。

[位运算优化代码](https://atcoder.jp/contests/dp/submissions/34604402)

# G - Longest Path

DAG 图上做 DP，结合拓扑排序

$$
DP[i] = max(pred[j]) + 1
$$

DAG 需要出边的临接表，并记录入边数量。为了方便，这里可以不一次求好 $DP[i]$，而是在遍历前驱点的时候，顺带更新 $DP[i]$。每个点被遍历到时，其前驱点都已经完成遍历，所以 $DP[i]$ 也已经确定了。这样就不用记录两个临接表了。

[代码](https://atcoder.jp/contests/dp/submissions/34526356)

# H - Grid 1

输入是 $N*M$ 规模的那么就是朴素的递推（也被叫做 DP 但实际上不涉及最优化决策问题）

[代码](https://atcoder.jp/contests/dp/submissions/34526732)

# I - Coins

概率计算。目标是求$tails \le heads$ 的数量，转换一下可以得到 $ tails \le \frac{N}{2}$ 。用表计算每个 tails 的数量的概率，并且只需要记录到 $\lfloor\frac{N}{2}\rfloor$ 为止。

$$
DP[i][j] = DP[i-1][j] * p[i] + DP[i-1][j-1] * (1-p[i])
$$

因为是连续计算，所以用单个数组逆序计算可以更加节约。
边界处理可以用出血法规避掉判断。
遇到的坑是%lf 输出的精度不够，需要指定一下精度。

[代码](https://atcoder.jp/contests/dp/submissions/34585281)

# J - Sushi

期望计算。

由较少盘子的期望推导出增加盘子的期望是困难的，但是在相同盘子数量的情况下可以列出这样的递推公式：

设 $W$ , $X$ , $Y$ , $Z$ 分别为空盘子、1 个寿司、2 个寿司、3 个寿司的盘子数量，那么根据选中不同盘子的概率，可以列出如下递推式：

$$
\begin{aligned}
DP[w][x][y][z] = & 1 + \\
 & \frac{w}{n}DP[w][x][y][z] + \\
 & \frac{x}{n}DP[w+1][x-1][y][z] +  \\
 & \frac{y}{n}DP[w][x+1][y-1][z] + \\
 & \frac{z}{n}DP[w][x][y+1][z-1]
\end{aligned}
$$

注意这个递推式中包含自己，需要消掉

$$
\begin{aligned}
(1 - \frac{w}{n})DP[w][x][y][z] = 1 + & \frac{x}{n}DP[w+1][x-1][y][z] +
  \frac{y}{n}DP[w][x+1][y-1][z] +
  \frac{z}{n}DP[w][x][y+1][z-1] \\
\end{aligned}
$$

$$
\begin{aligned}
DP[w][x][y][z] = & \frac{1 + \frac{x}{n}DP[w+1][x-1][y][z] +
  \frac{y}{n}DP[w][x+1][y-1][z]  +
 \frac{z}{n}DP[w][x][y+1][z-1]
}{1 - \frac{w}{n}} \\
= & \frac{n + xDP[w+1][x-1][y][z] +
  yDP[w][x+1][y-1][z]  +
 nDP[w][x][y+1][z-1]
}{n - w}
\end{aligned}
$$

因为一直有 $N = n = w+x+y+z$ ，所以状态上我们只需要记录三维，也就是：

$$
DP[x][y][z] = \frac{N + xDP[x-1][y][z] +
  yDP[x+1][y-1][z]  +
 nDP[x][y+1][z-1]
}{x+y+z}
$$

还注意到上述公式的求解顺序，当 $z$ 减少的时候 $y$ 会增加， $y$ 减少的时候 $x$ 会增加，所以 $z$ 需要作为外层循环， $x$ 作为内层循环。求解范围上， $x$ 最大要求解到 $N-y-z$ ， $y$ 最大要求解到 $Y+Z-z$ ， $z$ 最大要求解到 $Z$ 。如果理不清楚这个的话，全部求解到 $N$ 在复杂度上也没有明显差异。

> 即使做了出血， $DP[0][0][0]=0$ 还是要特判的。

[代码](https://atcoder.jp/contests/dp/submissions/34600315)

# K - Stones

取石子问题，这是必胜态必败态连续计算的问题，但是限定只能取某些数量的石子。

设 $DP[i] ∈ [0, 1]$ ，其中 $0$ 表示必败， $1$ 表示必胜，那么只有能到必败态的才是必胜态，不能到必败态的就是必败态，表达出来这样：

$$
\begin{align}
DP_i = & NOT(AND_{j=1}^K(DP_{i-a_j}) \\
      = & OR_{j=1}^K(NOT(DP_{i-a_j}))
\end{align}
$$

可以用 $O(N*K)$ 求解。
注意因为 $DP[i]$ 都是 0、1 值，因此可以用位运算批量计算求解，这需要一些技巧。
原理是，将 64 以内的 $a_i$ 和 64 以上$a_i$的分开处理，64 以上的采用位运算一次计算 64 位，而 64 以内的逐位处理。两者只要有一个为 1，答案就为 1。另外根据经验， $N$ 较多的时候 通常 1 远多于 0，因此 64 以内的部分采用更新的方法更新上去，可以仅在找到 0 的时候进行批量更新相关的值至 1。

[代码](https://atcoder.jp/contests/dp/submissions/34603641)

另一种思路：只是为了找 0，而可预计当 $N$ 较大时，大部分情况 0 总是远少于 1 的。

因此反向搜索，链表找所有的 0，直到超过 K 为止。

[代码](https://atcoder.jp/contests/dp/submissions/34640186)。

还希望通过链表查找 0 来加速，但是实际上复杂度仍然不会低于 $O(K)$ ，所以并不会更快 [代码](https://atcoder.jp/contests/dp/submissions/34639717)

# L - Deque

正经思路是 $O(N^2)$ DP，记录开头和结尾的坐标。不必单独用一个维度计算轮到谁了，因为这是可以根据奇偶性算出来的，所以是唯一确定的。

$$
DP_{l,r} = max(a_l - DP_{l+1,r}, a_r - DP_{l,r-1})
$$

计算顺序上要确保由短及长，因此可以按 $r-l$ 的顺序来计算。

[代码](https://atcoder.jp/contests/dp/submissions/34623200)

如果理不清楚上述计算顺序，可以考虑记忆化搜索。某些语言的偷懒记忆化搜索甚至是自定义 hash 都据说被卡了，但是认真做标记数组来完成记忆化搜索还是很快的：

[记忆化搜索](https://atcoder.jp/contests/dp/submissions/34623313)

# M - Candies

先列公式，第一个维度是当前遍历到的小朋友，第二个维度是总计的蜡烛数量。

$$
DP_{i, k} = \Sigma_{j=0}^{k}DP_{i-1,k-j}
$$

中间求和直接暴力求和复杂度为 $O(NK^2)$ 不能接受。注意到这里只是简单的连续求和，可以采用前缀和 或 差分方法优化，复杂度为 $O(NK)$ 。这样双数组的计算过程，更可以天然应用滚动数组，因此只需要记录一行的 DP。

[代码](https://atcoder.jp/contests/dp/submissions/34623588)

# N - Slimes

基础的思路是 $N^2$ 的空间和 $N^3$ 的时间：

$$
DP_{i,j} = min_{k=i+1}^{j}(DP_{i,k-1}+DP_{k,j}) + \Sigma_{k=0}^{j}w_k
$$

然而[这里](https://atcoder.jp/contests/atc002/tasks/atc002_c)有个两个更优的思路，分别是 $O(N^2)$ 和 $O(NlgN)$ 的时间

$N^2$ 的思路如下，令：

$$
p_{i,j}= argmin_{i\le k\lt j}\{c_{i,k}+c_{k+1,j}\}
$$

$p_{i,j}$ 实际上表示的就是 i,j 的最佳分割点。

$$
k_0 = p_{i,j-1}, k_1=p_{i+1,j}
$$

$k_0$ 和 $k_1$ 分别表示当前串去掉第一个元素和最后一个元素的最佳分割点。

$$
c_{i,j} = min_{k_0 \le k \le k_1}\{c_{i,k}+c_{k+1,j}\} +  \Sigma_{k=0}^{j}w_k
$$

那么当前串的最佳分割点一定在它们之间。直观的理解的话，就是 $k_0$ 加入 $w_j$后，右边变的更重了，而 $k_1$ 加入 $w_i$ 后，左边变的更重了，所以最佳答案应该在他们之间。

严格证明见[OIWiki: 四边形不等式优化](https://oi-wiki.org/dp/opt/quadrangle/)

之后的计算过程，计算指定长度的时候，对每个不同的 i，对应的 k 范围恰好是一个连续序列（相邻的重叠一个元素），所以累计不超过 $O(N)$ 时间。后面的加成部分也可以用前缀和或滑窗连续计算求出。总计 $O(N^2)$ 。

[代码](https://atcoder.jp/contests/dp/submissions/34707328)

nlgn 算法称为[Hu-Tucker Algorithm](https://math.mit.edu/~shor/PAM/hu-tucker_algorithm.html)，证明据说更加的难了。这里不详细分析了（我自己还在学习中）

# O - Matching

基础思路是二进制状态压缩，每进一个人维护下所有匹配组合的数量。时间复杂度 $O(N^22^N)$ 。
因为每个人都必须被匹配到，所以我们只需要关心每一层中，1 的个数与当前层相同的位。这样每层需要遍历的数可以减少很多，加起来是 $2^N$ 规模，所以整体复杂度降低到 $O(N2^N)$ 。
运算过程中，因为每一层必然要增加 1 个，所以我们也只需要关注到状态为 1 且当前层可以去选择的位置，这里可以用一个二进制与来表达。

[代码](https://atcoder.jp/contests/dp/submissions/34711028)

# P - Independent Set

树上做 DP 。
然后可以用类似拓扑排序（实际不是拓扑排序，而是不断找叶子）的办法完成 O(N)的无递归的树状 DP，只是每次移出的是度为 1 的点。
可以记录每个点黑白两种状态的组合数，但是更方便的是记录 白 和 白+黑 两个组合数，便于后续计算。
边界情况：只有 1 个点的时候，没有度为 1 的点。

[代码](https://atcoder.jp/contests/dp/submissions/34711649)

# Q - Flowers

令 $DP[i]$ 为以第 i 朵花为结尾的最大分数，那么

$$
DP_i = max_{1 \le j \lt i, h[j]<h[i]}(DP_j) + a_i
$$

直接求是 $O(N^2)$ 的，但是 max 过程可以采用线段树在 $O(lgH)$ 时间求解，因为 $1\le h_i\le N$ ，所以整体复杂度在 $O(NlgN)$ 。

[代码](https://atcoder.jp/contests/dp/submissions/34197712)

# R - Walk

计数问题， $N$ 不大但是 $K$ 出奇的大。用 $DP_{i,j}$ 表示第 $i$ 步后处于 $j$ 位置的组合总数，那么有：

$$
DP_{i,j} = \Sigma_{k∈[k | a_{k,j}=1]}(DP_{i-1,k})
$$

很显然上述属于线性递推式，可以用矩阵求幂的方法在 $O(N^3lgK)$ 时间求解

> 有更低复杂度的矩阵乘法但是 atcoder library 里居然没有。

[代码](https://atcoder.jp/contests/dp/submissions/34311602)

# S - Digits

$K$ 巨大而 $D$ 比较小，显然进行数位 DP。

考虑用一个维度保存模 $D$ 的余数。为了区分是否小于 $K$ ，需要另一个维度。 $DP_{i, mod, 0}$ 表示到第 i 位为止比 $K$ 的前缀 小的模 $D$ 为 $mod$ 数字总数，而 $DP_{i, mod, 1}$ 表示和 $K$ 的前缀相等的模 $D$ 为 $mod$ 数字总数。

可以发现对于相同的 $i$ ，$DP_{i, mod, 1}$中仅有一个为 1，其余都为 0，因此这部分可以单独拆开进行优化。

本题不必排除先导 0，但是需要排除 0 这个选项，所以答案需要-1。另外需要注意 K 本身可能是 D 的倍数。

[代码](https://atcoder.jp/contests/dp/submissions/34715528)

# T - Permutation

这题的难点在于设计转移方程。由于 N 比较大，状态压缩是不可行的。

注意到前 $n-1$ 个数字组成一个满足输入前 $n-2$ 个约束的不完全排列，假设最后一个数字为 k ，我们可以理解为最后插入了数字 $k$ ，前面大于等于 $k$ 的数字都增加了 1 ，这样 前 $n-1$ 个恰好就是满足约束条件的完整排列了。

因为新插入的数也要满足约束，所以我们记录 $DP_{i,j}$ 为 1~i 数字组成的，满足前 $i-1$ 个约束的，最后一个数字为 $j$ 的组合总数，可列出递推公式：

$$
DP_{i,j} = \begin{cases}
\Sigma_{i=j}^{i-1}DP_{i-1,k} & s[i-1]='<' \\
\Sigma_{i=1}^{j-1}DP_{i-1,k} & s[i-1]='>' \\
\end{cases}
$$

该求和过程可以用前缀和优化，总复杂度 $O(N^2)$

[代码](https://atcoder.jp/contests/dp/submissions/34717337)

# U - Grouping

状态压缩 DP， 用二进制表示每一个兔子是否已经被编组的状态。

我们可以预处理的方法计算好每个分组的分值，该计算过程 $O(2^N)$ 。

计算每个状态的分值时，其最后一个兔子必然在某个分组里，因此仅需考虑最后一个兔子的分组状态。

枚举一个组合的合法的子分组状态时，需要使用二进制技巧：我们从选择组合中的所有兔子出发，然后 `((j-1) & i)` 就是下一个状态。因为这个操作表达的是：将为 1 的最低位的兔子变成 0，同时将所有更低位的兔子由 0 变成 1。

中止条件 `(i^j)<j` 其实表达的是，确保 j 和 i 的最高位相同。如果相同，`i^j` 的对应为 1，则必然小于 j。如果不同，则`i^j`的对应位为 1，必然大于 j。

整体复杂度 $O(3^N)$ 。

[代码](https://atcoder.jp/contests/dp/submissions/34718145)

# V - Subtree

题目中的额外条件“黑点只能通过黑点到达别的黑点”其实就是所有黑点必须组成一个连通块。

思路完全和[这篇文章](https://blog.csdn.net/Emm_Titan/article/details/123875298) 一致，一次由叶子向上的，计算当该节点为黑色时，孩子有多少种组合情况；一次由上向下的计算，计算当该节点为黑色时，父节点及兄弟节点有多少种组合，计算后者时利用前缀积和后缀积来动态排除自己的组合数。该文章代码里有但是描述里没提到的是，父亲也可以是白色，所以额外加 1。

这里展示另一种非递归写法，采用出栈时将所有孩子入栈的方法完成自顶向下遍历，直接记录该顺序供后续使用，逆序即为自底向上。

[代码](https://atcoder.jp/contests/dp/submissions/34719389)