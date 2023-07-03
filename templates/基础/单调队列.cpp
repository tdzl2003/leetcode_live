// 单调队列可用于在双指针遍历过程中求指针区间范围内的最大/最小值
// 当_Pr为 less的时候，max返回最大值；为greater时返回最小值。

template<typename T, class _Pr = less<T>>
class monotonic_queue {
private:
    deque<T> c;
    _Pr comp;
public:
    monotonic_queue() = default;
    explicit monotonic_queue(const _Pr& _Pred) : comp(_Pred) {}

    void push_back(T v) {
        while (c.size() && comp(c.back(), v)) {
            c.pop_back();
        }
        c.push_back(v);
    }
    void pop_front(T v) {
        if (v == c.front()) {
            c.pop_front();
        }
    }
    T max() {
        return c.front();
    }
};
