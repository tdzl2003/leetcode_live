## T1

简单题，设置一个计数器，遇到E则加1，遇到L则减1，并记录过程中出现过的最大数字即可。

## T2

求区段未被覆盖的面积。可以采用延迟线段树进行操作，不过更简单的方法是对区段进行排序（先按左端点再按右端点），排序后可以用一个循环计算出空白区间。

