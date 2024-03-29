
# 组合计数题解串讲

[@解题十分钟](https://space.bilibili.com/381371294)

---

# 加法原理

* 从分类角度理解：若对象或过程可以被分成无重复遗漏的若干类，每类的数量为 $a_i$ ，那么总数量为 $\sum a_i$
* 从集合角度理解：集合 $S$ 可以划分成若干相互独立的子集 $A_i$， 那么有：$|S|=\sum_i|A_i|$

---

# 乘法原理

* 从分步骤角度理解：若过程可以被分为相互独立的若干阶段，每个阶段的方法数为 $a_i$ ，那么总方法数为 $\prod a_i$
* 从集合角度理解：假设有若干集合 $Ai$ ，从每个集合中取出一个元素的组成的方案集合 $S$（2个集合时为笛卡尔积），总数为 $|S|=\prod_i|A_i|$

---

# 加法原理逆运用

* 若有数量为 $s$ 的对象中有一类数量为a，不属于这类的数量为 $s-a$
* 从集合角度理解，若集合 $A \subset S$，有 $|S-A| = |S|-|A|$
* 后俗称为“减法原理”

---

#### [ABC 279 G - At Most 2 Colors](https://atcoder.jp/contests/abc279/tasks/abc279_g)

一个长度为N的串，每格可以是C种颜色之一。要求任意连续的K个格子都不超过2种不同的颜色。

问总共有多少种符合条件的串。

---

# 排列组合

* 幂 $a^k$
* 排列$P$
* 组合$C$

---

#### [ABC 281 G - Farthest City](https://atcoder.jp/contests/abc281/tasks/abc281_g)

求有多少个无向图，满足N号顶点是唯一距离1号顶点最远的点。

---

# 多重排列组合

* 分球8问题

---

# 组合化简

* [范德蒙德卷积](https://oi-wiki.org/math/combinatorics/vandermonde-convolution/)

---

#### [CF 785 D - Anton and School - 2](https://codeforces.com/problemset/problem/785/D)

**题意**：给定一个由左右括号组成的序列，问其有多少个子序列是“标准简单括号序列”，“标准简单括号序列”的定义是长度为$2k$，前$k$个是左括号，后$k$个是右括号，如`((()))`

---

# [容斥原理](https://oiwiki.com/math/combinatorics/inclusion-exclusion-principle/)

* 简单表述：$|A\cup B| = |A|+|B|-|A \cap B|$
* 注意复杂度，一般更常用于集合之间对称的情况。

---

#### 倍数

给不超过20个元素的数组 $ai$，求M以内能被至少一个 $ai$整除的数的个数。

---

#### 错排问题

问1到N的所有排列$\{P\}$中，满足$P_i\ne i$的个数

---

# 分治思想

* 许多计数问题通过将问题分解成规模更小的问题来求解。

---

#### [括号匹配问题](https://www.bilibili.com/video/BV1hK4y1s7Ln)

问N组括号有多少种合法的排列方式（合法指括号能两两配对）

---

#### [AGC 060 A - No Majority](https://atcoder.jp/contests/agc060/tasks/agc060_a)

给一个模板序列，里面的?可以任意指定为小写字母，问有多少种方法，使得任意子串中，没有一个字母占据超过一半的比例。

---

# 映射法

* 直观理解，如果每个$A$过程都能唯一对应一个$B$过程，且每个$B$过程都能唯一对应一个$A$过程，那么 $|A|=|B|$
* 集合角度说，若集合 $A, B$ 之间存在双射关系 $f$，那么有 $|A|=|B|$

---

#### [ARC 153 A - AABCDDEFE](https://atcoder.jp/contests/arc153/tasks/arc153_a)

求第N小的，满足 `AABCDDEFE` 形式的整数。

---

#### [ABC 284 G - Only Once](https://atcoder.jp/contests/abc284/tasks/abc284_g)

给一个数组A，其中每个元素都是1到N之间；从 $i$ 出发，每次把当前的数作为下标访问下一个数，得到一个序列。 $S_i$ 表示该序列中仅出现一次的数的数量。

对于给定的N，总共有 $N^N$种可能的序列，问这所有可能性中，所有 $S_i$ 的和，模 $M$ 取余输出。

---

# 对称/互补法

---

#### [ARC 147 D - Sets Scores](https://atcoder.jp/contests/arc147/tasks/arc147_d)

$S$ 为$N$个 $\\{x|1\le x \le M\\}$ 的子集，其中相邻的两个集合只相差一个元素。

令 $score(S)=\prod_{i=1}^M(|\\{A|A \in S, i \in A\\}|)$

$score(S)$表示1到M中每个数字出现次数的积

求所有符合条件的$S$的分数之和。

---

# 区段求和优化

* 前缀和
* 树状数组
* 线段树
* 离散化
* CDQ分治（归并）：尤其适用解决时间有序的操作查询混合问题。

---

#### 例题

> 这题是在LC上看到的，但没找到题源，欢迎补充

给定一个数组$a_i$ 和两个数 $u, v$ ，问有多少组 $(i,j)|1\le i \le j \le n$，满足 $ u \le \sum_{i\le k \le j} a_k \le v$ （有多少组连续区段和在u和v之间）

---

#### [POJ 3387 - Crazy Thairs](http://poj.org/problem?id=3378)

给一个数组，问有多少组 $\{i,j,k,l,m\}$ 满足：$1\le i<j<k<l<m\le N$， $A_i<A_j<A_k<A_l<A_m$。

---

#### 132排列问题，改编自[LC 456 - 132 模式](https://leetcode.cn/problems/132-pattern/)

给一个数组，问有多少组 $\{i,j,k\}$ 满足：$1\le i<j<k\le N$，$A_i<A_k<A_j$。


---

# 偏序优化

* 双指针、三指针

---

#### 例题

> 这题是在LC上看到的，但没找到题源，欢迎补充

给定两个有序数组$a_i, b_i$ ，问有多少组 $(i,j)$，满足 $ u \le b_j-a_i \le v$ （有多少组连续区段和在u和v之间）

---

#### [LC 923. 三数之和的多种可能](https://leetcode.cn/problems/3sum-with-multiplicity/)

给定一个整数数组 arr ，以及一个整数 target 作为目标值，返回满足 i < j < k 且 arr[i] + arr[j] + arr[k] == target 的元组 i, j, k 的数量。


---

# 矩阵乘法

* 用于求解线性递推式，尤其是二维线性递推式。
* 压缩矩阵维度是关键。
* 一维线性递推有不少时候都可以通过母函数得到一个更好的解，但是矩阵方法简单易学。
* 许多字符串计数问题可以通过状态机转变为线性递推问题求解。

---

#### 平铺问题

$1\times 2$的方块平铺$3\times N$的矩形，问有多少种平铺方案？

#### catcat

问有多少个长度为N的小写字母串，其中恰好出现了两次连续的cat

---

# 卷积

* 定义：$c_i=\sum_{i=0}^na_ib_i$
* 快速傅里叶变换(FFT)利用了复空间，可以在$O(nlgn)$时间求出卷积。
* atcoder_library里有一个基于modint的实现，更适用于计数题。

---

#### [LC 576. 出界的路径数](https://leetcode.cn/problems/out-of-boundary-paths/)

---

#### [ABC 287 F - Components](https://atcoder.jp/contests/abc287/tasks/abc287_f)

给一个树，针对1到N之间的每一个x，问该树有多少个“非空导出子图”，正好有x个连通块。

> 导出子图，指从原图中选定顶点的子集，若原图中某个边的两个顶点都在子图中，则该边也包含在子图中。 

---

# 母函数

* 常用于组合式化简、求解通项公式、其它数学化简等各种场景
* 在许多场景是终极解决方案。
* 常结合广义牛顿二项式定理、泰勒展开、拉格朗日反演等数学工具使用。

---

#### [偶数个5问题](https://blog.csdn.net/weixin_39491014/article/details/107262070)

**题意**：问n位十进制数中，有多少个数中出现了偶数个5

# 其它今天没涉及到的方法

* 群论：置换群，轮换
* 涉及二进制的方法，如二进制状态，二进制集合运算，二进制1计数等等
* 非组合的概率计算