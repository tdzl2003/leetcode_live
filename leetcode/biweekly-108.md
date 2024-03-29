[比赛链接](https://leetcode.cn/contest/biweekly-contest-108/)

## T1

暴力可过。这里介绍 $O(N)$ 的准确做法，需要处理好边界：

* $i$ 从 $0$ 开始循环
* 找最长的从 $i$ 开始的合法串，可以用 $a_j-a_i = (j-i \bmod 2)$ 来检查。
* 下一个串可以从上个合法串的结尾开始找。
* 如果 $i$ 开始没有合法串（长度为1），下一个串要从 $i+1$ 开始找

> 不能从结尾的下一个开始找，否则第一个示例就会出错。

## T2

简单题，用一个set记录所有位置并维护即可。根据题意，不必记录石头的数量。


## T3

s的长度很短，因此可以预处理好所有合法的5的幂（或打表），然后进行DP甚至是DFS都可以完成本任务。

## T4

遍历 $n*m$ 的格子显然会超时。

可以采用哈希表统计每一个黑格的坐标，然后可以通过仅在一个格子周围遍历来找到所有有黑格的方块。剩下的就是没有黑格的方块。

注意如果有多个黑格在同一个方块，可能会重复计数，这里有两个简单的办法来解决这个问题：

1. 仅当当前黑格是方块中的第一个黑格时才计数
2. 重复计数的次数等于方块中黑格的数目，所以可以重复计数后将数量除以黑格的数目。

最后用 $n*m$ 减去所有非空方块的数目，就是空方块的数目。

> 其他人的思路比我的更简单，我还绕了点
> 
> 其它人的思路是：直接用哈希表记录包含黑格的方块坐标，这样一次循环统计就可以了。