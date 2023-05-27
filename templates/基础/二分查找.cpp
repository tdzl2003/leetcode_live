
// 在[min,max]之间寻找最大的满足test(t)为true的t，若全不满足，返回min-1；若全都满足，返回max。
// test需满足单调：不存在i<j 且test(i)=false, test(j) = true
template<typename T, typename F>
T bsmax(T min, T max, F test) {
    min--;
    while (min < max) {
        auto mid = (max + min + 1) / 2;
        if (test(mid)) {
            min = mid;
        }
        else {
            max = mid - 1;
        }
    }
    return min;
}


// 在[min,max]之间，寻找最小的满足test(t)为true的t，若全都满足，返回min；若全不满足，返回max+1
template<typename T, typename F>
T bsmin(T min, T max, F test) {
    min--;
    while (min < max) {
        auto mid = (max + min + 1) / 2;
        if (!test(mid)) {
            min = mid;
        }
        else {
            max = mid - 1;
        }
    }
    return min + 1;
}