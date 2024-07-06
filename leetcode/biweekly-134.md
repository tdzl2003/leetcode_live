## T1

简单题，按题意遍历即可。

一种提升手速的处理循环的办法是，将数组中前2个元素复制到末尾，这样就不必处理循环了。

## T2

阅读理解题。

显然最佳策略是盯着energy最低的敌人猛薅，依次标记其他敌人。但需要先判断初始能量够不够薅一次，否则不能去标记别人。

## T3

因为k的范围比T1大了，所以需要处理复杂度问题。

首先依然可以用T1的技巧，将前 $k-1$ 个元素复制到末尾。

然后求出每段最长的交替段落，设其长度为L，其中就有 $max(0, L-k+1)$ 个子数组符合条件。

这样就可以在 $O(N+K)$ 时间内解决本题。

## T4

注意从任何一个位置开始，连续AND的结果随着子数组变长必然是个单调不上升的序列。

因此最简单的办法就是构建线段树，然后采用二分查找找到符合条件的左右边界，即可以在 $O(Nlg^2N)$ 时间内解决本题。

严格的定义：

$$
L(i) = min_j(and(A_i..A_j) \le k) \\
R(i) = min_j(and(A_i..A_j) \lt k) \\
res = \sum_{i=0}^{n-1} R(i)-L(i)
$$

利用 $and(A_i..A_j)$ 关于 $j$ 的单调性二分查找求解，利用线段树快速计算。

## T4 + LogTrick

采用灵神发明的 [LogTrick](https://leetcode.cn/problems/minimum-sum-of-values-by-dividing-array/solutions/2739262/golang-logtrickxian-duan-shu-you-hua-dp-svcz8/) ，可以在 $O(NlgU)$ 时间内解决本题

