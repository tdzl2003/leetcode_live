## T1

定理：两个数的最小公倍数乘以最大公约数 等于它们的乘积 （然而这个定理对这题没有用）

在最多移除一个元素的情况下，可以依次处理前后缀的最小公倍数和最大公约数，找到最大的乘积，时间复杂度 $O(N)$

当然，对本题来说，暴力也可以通过

## T2

字符串的顺序和长度无关，所以其实只需要统计每个字符的数量 进行迭代递推即可。

本题直接暴力可以使用 $O(N+|E|t)$ 的复杂度通过。

通过观察公式，可以省去轮换的步骤，优化到 $O(N+t)$ 时间。（相当于分成两个步骤：先把所有的z换成za，然后再滚动1格）

如果采用矩阵快速幂，还可以在 $O(N+|E|^3lgt)$ 时间通过。使用母函数或类似分治法，可能也有希望得到更低复杂度的方法（去掉几个 $|E|$ ）。

## T3
