# 网络流与最小割

2022 年 7 月 19 日晚上 21:30 在[解题十分钟直播间](http://live.bilibili.com/23271987)讲解最小割解题方法和系列例题。
 
直播录像在[这里](https://www.bilibili.com/video/BV1jt4y1t7pd/)

网络流的定义：

- 有一个 s 点有一个 t 点，以及若干其它点
- 有若干有向边。其中 s 点没有入边，t 点没有出边
- 对于除了 s 点和 t 点以外的所有点，入流量之和等于出流量之和
- 形象的比喻想象水管，s 点是无限的水源，t 点是无限的出口，边的权值等于管的容量
- 整个网络同时能通过的最大流量，这个流量等于 s 点的所有出流量，等于 t 点的所有入流量

割的定义：

- 设置两个集合 S 集合和 T 集合，且 s 点属于 S 集合，t 点属于 T 集合
- 其它所有点属于 S 集合或 T 集合之一
- 所有来自于 S 集合，指向 T 集合的边，权值之和为割的大小

定理：

- 最小割 = 最大流
- 直观理解就是 最小割的边满流的情况下，无法再找到增加流量的办法

能否套用最小割方法的判断：

1. 把最少/最小代价对应到最小割
2. 把二元选择问题 改变为集合选择问题
3. 不合法的方案，定义成流量无穷大的边

建图过程：

1. 根据可以做二元选择的对象定义所有的点
2. 根据不合法方案连接无穷大的边，明确点的集合归属含义
3. 根据点的集合归属含义，明确所有需要支付的成本

额外思路：

1. 先假设能获得所有收益，然后把得不到的收益也记作成本，来解决最大化收益问题

---

# 棋子问题

有 N\*M 的棋盘，上面有 K 个棋子，位于 Ai 行 Bi 列。

一次操作可以消除一行的棋子或者消除一列的棋子。

问最少要多少次操作，才能消灭所有的棋子？

1 ≤ N,M ≤ 100

思考过程：

- 最少次操作 => 最小代价 => 最小割（把边看做代价）
- 每一行，可以选择消除或不消除
- 每一列，可以选择消除或不消除
- 所以网络中的点是 行 与 列
- 不合法的方案，表示有棋子没有被消除。

建模过程：

- 行属于 S 集合表示不消除，属于 T 集合表示消除
- 列属于 T 集合表示不消除，属于 S 集合表示消除
- 不合法方案的边：
  - 对于为 1 的单元格，行不消除且列不消除非法
  - 对应单元格建立行指向列的无穷大流量边
- 支付成本：
  - s 到行，流量为 1
  - 列到 t，流量为 1

---

# 设备采购问题

有 N 种设备，采购价格分别是 A1,A1,...AN

和 M 个项目，项目收益分别是 B1,B1,...BM

另外有 K 个约束条件，Ci,Di 表示完成 Di 号项目，必须要拥有 Ci 号设备。

问最高能获得的利润是多少（利润等于收益-成本）

思考过程：

- 先假设能获得所有收益，然后把得不到的收益也记作成本
- 设备：采购与不采购；项目：做与不做
- 不合法方案：项目依赖的设备没有采购，但又要做对应项目

建图过程：

- 设备属于 S 集合表示不采购，属于 T 集合表示采购
- 项目属于 S 集合表示不做，属于 T 集合表示做
- 不合法方案：
  - 项目依赖设备，但设备未采购，不合法
  - 有依赖时，从设备指向项目，流量无穷大
- 支付成本：
  - 设备采购支付成本，s 点指向设备，流量为采购成本
  - 项目不做支付损失，项目指向 t 点，流量为项目收益

---

# 取数问题

在一个 M\*N 的棋盘中，每个方格有一个正整数。现在要从方格中取若干个数，使任意 2 个数所在方格没有公共边，并使取出的数总和最大。试设计一个满足要求的取数算法。

思考过程：

- 先假设能获得所有数，然后建图使方案合法
- 每个数选择与不选择
- 不合法的方案：相邻的格子不能同时选

建图过程：

- 经过尝试和思考，得出结论，区分坐标奇偶性（横坐标和纵坐标之和的奇偶性）
- 偶数格属于 S 集合表示选择，属于 T 集合表示不选择
- 奇数格属于 T 集合表示选择，属于 S 集合表示不选择
- 不合法方案：
  - 相邻的格子不能同时选
  - 相邻的格子，从偶数格向奇数格建边，流量无穷大
- 支付代价
  - 偶数格不选择，s 向偶数格建边，流量为格子的值
  - 奇数格不选择，奇数格向 t 建边，流量为格子的值

---

# 另一个棋子问题

本题来自于[AtCode ABC259](https://atcoder.jp/contests/abc259/tasks/abc259_g)

有 N\*M 的棋盘，每个方格有一个数，其中有正数也有负数。要求选定其中的若干行和若干列，满足：

- 要求负数的格子不能同时选择所在行和所在列。

如果方格所在的行或所在的列被选中，它的分数被加到总分上，不论是正数还是负数。如果行和列同时被选中，分数也只累加一次。

试设计一个算法，问能得到的最大得分是多少。

思考过程：

- 记所有正数之和为最大收益，考虑需要支付的成本
- 行：选择与不选择，列：选择与不选择
- 不合法方案：负数格的行与列不能同时选择

建图过程：

- 行选择：属于 S 集合；不选择：属于 T 集合
- 列选择：属于 T 集合；不选择：属于 S 集合
- 不合法方案：
  - 负数格不能同时选择所在行和所在列
  - 负数格从行向列建立流量无穷大的边
- 支付成本：
  - 行选择，支付该行所有负数格成本，行到 t 连边，权值为该行所有负数的绝对值和
  - 列选择，支付该列所有负数格成本，s 到列连边，权值为该列所有负数的绝对值和
  - 正数格，行和列都不选择，支付放弃的成本，列到行建边，权值为该格的值
