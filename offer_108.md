# 单词演变

[题目链接](https://leetcode-cn.com/problems/om3reC/)

成功构图以后就是个朴素的BFS，主要在于如何低复杂度的构图。

一个基础的思路是两两比对，复杂度N^2

进一步的思路是将每个单词插入hash表，然后尝试修改每个单词的每个字符，去hash表里寻找，复杂度N * 26 * L

进一步改进方法，将每个单词的每个字符逐个屏蔽（替换成统一的字符如_），插入hash表（hash表内数量N * L个）；找的时候也是逐个屏蔽去Hash表里找，包含hash计算的时间复杂度N * L * L

进一步改进方法，采用一种特殊的hash方法，从而可以快速计算出“屏蔽某一个字符”的hash值。因为单词长度有限，所以可以直接采用27进制编码来完成这个hash，hash结果不超过2^48，可以用Number/int64来表达。这样，“屏蔽某一个字符”的hash值即为减去这个字符所产生的hash值

> 如果单词进一步变长，依然可以采用这种办法hash，超出int64的部分循环可至低位进行相加或异或，只要位数足够，碰撞率不高，依然可以维持N*L的整体时间效率。

```js
/**
 * @param {string} beginWord
 * @param {string} endWord
 * @param {string[]} wordList
 * @return {number}
 */
const baseCh = "a".charCodeAt(0) - 1;
var ladderLength = function (beginWord, endWord, wordList) {
  // 规定_是0，a是1，以此类推
  const hashMap = {};
  const base = [1];
  for (let i = 1; i < beginWord.length; i++) {
    base[i] = base[i - 1] * 27;
  }

  const graph = [];

  for (let i = 0; i < wordList.length; i++) {
    graph[i] = [];
  }

  let target = -1;

  for (let i = 0; i < wordList.length; i++) {
    const word = wordList[i];
    if (word === endWord) {
      target = i;
    }
    let hash = 0;
    for (let j = 0; j < word.length; j++) {
      hash += base[j] * (word.charCodeAt(j) - baseCh);
    }
    for (let j = 0; j < word.length; j++) {
      const hash1 = hash - base[j] * (word.charCodeAt(j) - baseCh);
      if (!hashMap[hash1]) {
        hashMap[hash1] = [i];
      } else {
        for (const other of hashMap[hash1]) {
          graph[i].push(other);
          graph[other].push(i);
        }
        hashMap[hash1].push(i);
      }
    }
  }
  if (target < 0) {
    return 0;
  }

  const depth = [];
  const queue = [];

  {
    let hash = 0;
    for (let j = 0; j < beginWord.length; j++) {
      hash += base[j] * (beginWord.charCodeAt(j) - baseCh);
    }
    for (let j = 0; j < beginWord.length; j++) {
      const hash1 = hash - base[j] * (beginWord.charCodeAt(j) - baseCh);
      if (hashMap[hash1]) {
        for (const other of hashMap[hash1]) {
          if (other === target) {
            return 2;
          }
          queue.push(other);
          depth[other] = 2;
        }
      }
    }
  }

  let h = 0;

  for (; h < queue.length; ++h) {
    const curr = queue[h];
    const currDepth = depth[curr] + 1;

    for (const edge of graph[curr]) {
      if (depth[edge] != null) {
        continue;
      }
      if (edge === target) {
        return currDepth;
      }

      depth[edge] = currDepth;
      queue.push(edge);
    }
  }

  return 0;
};
```
