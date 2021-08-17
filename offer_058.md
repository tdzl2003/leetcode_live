# 日程表

[题目链接](https://leetcode-cn.com/problems/fi9suh/)

用一个排序树记录所有已登记的日程（因为日程不会重叠，所以按start、按end、按pair来排序，结果都是一样的）

然后每次book的时候在排序树内查找即可。

```C++
#include <map>

class MyCalendar {
public:
    std::map<int, int> records;

    MyCalendar() {
    }
    
    bool book(int start, int end) {
      auto itor = records.lower_bound(start);
      if (itor != records.end()) {
        if (itor->first < end)  {
          return false;
        }
      }
      if (itor != records.begin()) {
        --itor;
        if (itor != records.end()) {
          if (itor->second > start) {
            return false;
          }
        }
      }
      records[start] = end;
      return true;
    }
};
```