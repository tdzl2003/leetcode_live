[比赛链接](https://leetcode.cn/contest/biweekly-contest-107/)

## T1

简单题，按题意暴力比较即可。

可以采用hash表等方法在 $O(\sum|S_i|)$ 时间解决。

## T2

* AA后面可以接BB
* BB后面可以接AA或AB
* AB后面可以接AA或AB

总感觉可以贪心/找规律做掉，但是赛中最稳妥的做法还是采用DP。

需要注意的是test case比较多，需要对DP进行缓存。否则会TLE

关于贪心方法：

* 每两个BB之间必然有一个AA（只有AA后面可以接BB）
* 每两个AA之间必然有一个BB（AA后面只能接BB）

所以只需要考虑 BB和AA的循环，而AB可以插在任何一个BB之后，循环无限多次。

因此：

* 若BB比AA多，BB开始，否则AA开始
* AABB交替
* 所有的AB都可以用掉（因为题目范围 $y\gt 0$ )

答案为：

$$
(min(x,y) + min(min(x,y)+1, max(x,y)) + z)\times 2
$$

## T3

按题意进行滚动DP即可，状态中记录首尾字符，足以通过此题。

考虑实际有效的状态很少，还可以只记录一侧的字符，和最后一个单词存在了哪一侧，进行压缩。

## T4

因为X是固定的，按时间轴进行排序所有查询，进行双指针模拟，可以在 $O(QlgQ)$ 时间实现。

注意如果查询的是不确定长度的范围，仍然是可以离散化后使用莫队算法在 $O(Q\sqrt Q)$ 时间完成的。
