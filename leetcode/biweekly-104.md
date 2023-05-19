[比赛链接](https://leetcode.cn/contest/biweekly-contest-104/)

## T1

简单题，按提议找子串并进行字符串比较即可。

## T2

按每行排序，每列就是每次操作的一组数，然后线性遍历即可。这样总复杂度为 $O(NMlgM)$ 

## T3

乘以2相当于左移一位。可以看出得数的最高二进制位 越高，得数越大，因此必然最佳策略是将原数组中某个最高位为1的数连续操作k次。

（赛中此时我陷入了一个很复杂的贪心思路，考虑最高位为1的子集，剩下的数 找哪一个左移可以获得一个最高的二进制位。但是这是一个边界情况很多的思路，有时候一个数不左移反而能获得一个新的二进制位）

正确的思路是直接设法找到这个数。考虑把某个数左移k次的答案，是：

$$
OR(A_0, ..., A_{i-1}, A_{i+1}, ..., A_N) | (A_i\lt\lt k)
$$

注意到前面部分是典型的“排除掉自己剩下的数运算”，因此可以采用前缀/后缀预处理的方式，在累积 $O(N)$ 时间求得所有候选答案，最后取最大值返回即可。

## T4

组合计数题

将数组排序，考虑相同 $max,min$ 的每一组组合，其实就是选中这两个元素，然后在这两个元素之间的元素任意选择。假设之间有 $k$ 个元素，就有 $2^k$ 种组合。

唯一的特例是 $max=min$ ，此时同为一种组合。单独处理这类情况。

以上说明假设的是数组中每个元素不同。实际上如果有元素相同，仍然可以通过规范 max/min 的定义得到相同的结论。

注意到当max迭代到下一个max时，加入了一个新的可能的min，而之前的min的系数全部恰好乘以2，因此可以在 $O(1)$ 时间完成迭代，在总计 $O(N)$ 时间完成本题。