# 子序列的数目

[题目链接](https://leetcode-cn.com/problems/21dk04/)

直播现场采用了一个N^3但可以通过累加减少到N^2的DP公式：

设F(i,j) = s前缀i刚好匹配到t前缀j的方案总数
F(i,j) = s[i] === s[j] ? sum(F(i-1, 0..j-1)) : 0
其中sum可以在遍历过程中连续求出，不引入额外复杂度。

```js
/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var numDistinct = function(s, t) {
  let a = new Array(s.length + 1).fill(0);
  a[0] = 1;

  for (let i = 0; i < t.length; i++) {
    const b = new Array(s.length + 1).fill(0);
    let sum = 0;
    for (let j = 0; j <= s.length; j++) {
      sum += a[j];
      if (s[j] === t[i]) {
        b[j+1] = sum;
      }
    }
    a = b;
  }
  let r = 0;
  for (let i = 0; i <= s.length; i++) {
    r += a[i];
  }
  return r;
};
```

其实可以直接求出N^2的状态转移方程：

设F(i,j) = s前缀i可以匹配t前缀j的方案总数
F(i,j) = F(i-1, j) + (s[i] === s[j] ? F(i-1,j-1) :0)

```js
var numDistinct = function(s, t) {
  let a = new Array(t.length + 1).fill(0);
  a[0] = 1

  for (let i = 0; i < s.length; i++) {
    const b = new Array(t.length + 1).fill(0);
    b[0] = 1;
    for (let j = 0; j <= t.length; j++) {
      b[j+1] = a[j+1];
      if (s[i] === t[j]) {
        b[j+1] += a[j];
      }
    }
    a = b;
  }

  return a[t];
};
```