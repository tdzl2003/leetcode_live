# 青蛙跳台阶问题

[题目链接](https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/)

首先列出式子：

$$
f(i)=\begin{cases}
1 & i=0 \\
1 & i=1 \\
f(i-1)+f(i-2) & i \ge 2\\
\end{cases}
$$

其解释为：对于 2 阶以上台阶的所有走法，都可以分为最后一步 走了 1 格的走法 和 最后一步走了 2 格的走法，其总数分别为$f(i-1)$和$f(i-2)$

- 基础递归法：高复杂度，复杂度为 $\Theta(f(i))$，为$\Theta((\frac{1 + \sqrt{5}}{2})^i)$
- 递推法：从前往后计算，复杂度为$\Theta(i)$
- 递推+滑动窗口：将空间复杂度降维$\Theta(1)$
- 矩阵求解法，时间复杂度为$\Theta(lgi)$

下面重点讲矩阵求解法。

我们设向量

$$A_{i}=[f(i), f(i+1)]$$

那么显然有：

$$
\begin{aligned}
    A_{0} =& [1,1] \\
    A_{i+1}= &[f(i+1),f(i+2)] \\
        =& [f(i+1),f(i)+f(i+1)] \\
        =& [0 * f(i) + 1*f(i+1), 1*f(i) + 1*f(i+1)] \\
        =& [f(i), f(i+1)] * \begin{bmatrix}
            0 & 1 \\
            1 & 1
        \end{bmatrix} \\
        =& A_{i} * \begin{bmatrix}
            0 & 1 \\
            1 & 1
        \end{bmatrix} \\
    A_{n} =& A_{0} * \begin{bmatrix}
            0 & 1 \\
            1 & 1
        \end{bmatrix}^n
\end{aligned} \\


$$

所以求出矩阵的幂，就可以快速的求出$A_n$，从而求出$f(n)$

为了进一步简化计算，代码里假设$A_{0} = [0,1]$，$A_{i}=[f(i-1), f(i)]$，因此$f(n)$就是$\begin{bmatrix}
            0 & 1 \\
            1 & 1
        \end{bmatrix}^{n+1}$的左下角矩阵元。

对于求矩阵的幂，因为矩阵乘法符合结合律（注意不符合交换律），因此可以采用分治法递归求出，也可采用将指数二进制分解的方法求出。这里采用二进制分解指数的方法，原理类似：

$$
a^{10101} = a^{10000} * a^{100} * a^{1}
$$

因此不断用自乘的方法求出$a^{2^k}$，并根据指数的该二进制位情况决定是否乘上该矩阵即可。

```js
const mod = 1000000007n;

function mul(a, b) {
  const [i, j, k, l] = a;
  const [m, n, o, p] = b;
  return [
    (i * m + j * o) % mod,
    (i * n + j * p) % mod,
    (k * m + l * o) % mod,
    (k * n + l * p) % mod,
  ];
}

var numWays = function (n) {
  n++; // 实际求n+1
  const base = [0n, 1n, 1n, 1n]; // B
  let p = base; // B^(2^k)
  let r = [1n, 0n, 0n, 1n];

  for (let i = 0; ; i++) {
    const b = 1 << i;
    if (b > n) {
      break;
    }
    if (b & n) {
      r = mul(r, p);
    }
    p = mul(p, p);
  }

  return Number(r[2]);
};
```
