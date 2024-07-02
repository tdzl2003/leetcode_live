## T1

简单题，按顺序遍历也可以，二分查找也可以，按顺序打表也可以。

二分查找时，易得奇数行的总个数为 ${\lceil n\rceil}^2$ ，偶数行的总个数为 ${\lfloor n\rfloor}^2 + {\lfloor n\rfloor}$ 

## T2

有效子序列的等价定义为：

* 全部为奇数，或 全部为偶数， 或 奇偶相间

可以直接贪心枚举每一种情况求解，复杂度 $O(N)$ 。

## T3

一个序列是有效子序列，当且仅当：

* `(sub[0] + sub[1]) % k == (sub[1] + sub[2]) % k == ... == (sub[x - 2] + sub[x - 1]) % k`

该式成立当且仅当

* `sub[0]%k == sub[2]%k == ...`
* 且 `sub[1]%k == sub[3]%k == ....`

所以我们可以求出不同模k的所有下标序列，然后

* 对比每一个全部余数相同的下标序列
* 两两比对其最长的交替组合

这看起来是一个三重循环，但实际上因为所有序列的总长度是 $N$ ，所以复杂度实际为 $O(N^2+NK)$ ，足以通过。

同为平方级的做法，我的做法是较为复杂的，更简单的做法参见[灵神的题解](https://leetcode.cn/problems/find-the-maximum-length-of-valid-subsequence-ii/solutions/2826591/deng-jie-zhuan-huan-dong-tai-gui-hua-pyt-z2fs/)

