## T1

简单题，首先循环节是 $2(N-1)$ ，可以用k对循环节取模。

然后可以根据k的范围进行判断，分段直接求出最终的下标。

## T2

易看出过程为杨辉三角的一斜行，所以答案为 $C(n+k-1, k)$ ，可直接公式求解，复杂度 $O(n+k)$ 。

当然采用暴力 $O(nk)$ 求解也是足以通过本题的。

## T3&T4

变种背包，可以使用DP处理。如果手写可以原地处理。

正常需要处理 $2M$ 的范围，可以进一步进行贪心优化。

首先可以证明最佳方案中一定包含数组中最大的数（否则总是可以将方案中最大的数替换为数组中最大的数），所以仅需对比最大的数更小的数进行背包处理，这样只需要处理 $M$ 的范围，从而得到性能和空间上的提升。


