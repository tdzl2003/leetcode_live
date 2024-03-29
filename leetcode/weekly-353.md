[比赛链接](https://leetcode.cn/contest/weekly-contest-353/)

## T1

简单题，很容易证明答案是 $num + 2t$

## T2

因为只能从左往右跳，显然属于DAG，考虑DP解决。

简单DP题，按下标顺序进行DP，可在 $O(N^2)$ 时间内解决。

采用离散化+线段树，可以在 $O(lgN)$ 时间内完成最值查询，从而将整体复杂度降低到 $O(NlgN)$ 。

据说采用 [梵峨眉大悲寺树](https://en.wikipedia.org/wiki/Van_Emde_Boas_tree) 处理值域有希望做到更低。待研究。

## T3

简单DP题，计算每个位置分别选择每个数的最大长度即可。时间复杂度 $O(N)$ 

### T3变种

很多人读错题读成子序列（包括我自己，这里介绍子序列的解法。

按如下策略构造一个序列：

* 如果 $a_i=b_i$ ，只放一个数
* 否则，分别放入 $max(a_i,b_i)$ 和  $min(a_i,b_i)$

在这个序列中查找LIS，可以证明两个序列相同下标的数同时只能取到一个。时间复杂度 $O(NlgN)$

## T4

操作之间的顺序无关，所以按从左到右的顺序，可以依次确定每个下标需要进行操作的次数。

使用支持区间修改的线段树可以在 $O(NlgN)$ 时间解决。

直接从左到右的顺序迭代，使用队列维护未来的差分（或者用一个数组记录过去的差分并在未来查询，无本质区别），可以在 $O(N)$ 时间解决。


### T4变种

部分人读错题读成操作可以不连续（子序列）。该问题为证明题，设所有数的和为sum，必须有：

* $sum \bmod k = 0$
* $max\{A_i\} \le \frac{sum}{k}$

才有解。满足条件的情况下，可以总是操作最大的k个数得到合法解。
