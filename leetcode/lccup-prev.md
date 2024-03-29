## LCP 71. 集水器

为了统一处理，可以将每个格子分为四个部分（上下左右），然后根据地图可以确定连通关系。

分为两部分：首先，密闭空间无法填充水，需要保留为空。
然后考虑从水中拿出时，水可能向下流出直至平衡，过程类似于放水。

* 填水时，按题意，仅需floodfill：所有边缘、顶部、底部都是有水的；所有与水相邻且连通的格子都是有水的。
* 放水时，所有边缘和底部都肯定会放空；然后我们需要根据水的连通性判断：若水有连通、且相同或更低高度、且无水的格子，则该格也会无水。该过程可以简化表述如下：
    * 从上至下依次处理每一层。遍历每一层时，都从所有可能放空的路径开始搜索，但是仅将当前高度的格子放空。
    * 该流程可以正确处理上面某一层放空后水域断开连接，从而可能在另一侧保持更高液面的情况。

模拟完成后，统计保留颜色的节点数量即可。

## LCP 70. 沙地治理

找规律&证明题

找到的规律大致思路是一行行填充：

倒数第一行朝上的都放满，这样倒数第一行朝下的都会自动填充
倒数第二行尽量少放，只需要放第2个位置，其余的靠倒数第一行和倒数第三行自动填充
倒数第三行类似倒数第一行，不过留几个空给倒数第四行来自动填充
倒数第四行类似倒数第二行，只要放第1个位置，其余的靠倒数第三行和倒数第五行自动填充
重复1到4
第一行无论如何放第1个

证明较为复杂，赛中不太考虑证明。证明过程可参考：[这个题解](https://leetcode.cn/problems/XxZZjK/solution/zhao-gui-lu-han-jie-fa-de-zheng-ming-by-m43kf/)

## LCP 69. Hello LeetCode!

很难采用贪心解决，因此可采用状态压缩DP寻找最优解。

注意同一单词内也不可轻易贪心，因为单词长度有限，尽量同样采用状态压缩解决。

## LCP 68. 美观的花束

双指针计数题

显然一个区间如果合法，其子区间也合法。

因此考虑以每个位置为区间终点的所有区间，可以用双指针维护合法的最早起点，答案加上区间的长度即可。

## LCP 67. 装饰树

简单数据结构题，按题意模拟即可。

## LCP 66. 最小展台数量

简单题，按题意计算每天所需的展台数量并分类型记录最大需要展台数量，最后统计输出即可。

## LCP 65. 舒适的湿度

首先题目翻译为，使操作过程中的最大值和最小值之差最小。

记录 $DP[i][j]$ 为第i次操作后，当前为 $min+j$ 时的最小可能的 $max-min$。

那么：

* 如果当前选择为正数，下一个状态必为 $j+a[i]$ ，可能会产生新的 $max$ 从而更新 $max-min$
* 如果当前选择为负数，分两种情况：
    * 若 $j\ge a[i]$ ，下一个状态为 $j-a[i]$ ，且不更新 $max-min$
    * 若 $j\le a[i]$ ，下一个状态会产生新的 $min$ ，因此下一状态为 $0$ ，且必然更新 $max-min$

可以在 $O(nU)$ 时间内完成。

