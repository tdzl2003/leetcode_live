/*
作用：将一个值域空间较大的数组的值域压缩到N以内，常用于仅关心大小或相等关系，而不关心具体取值的情形
*/

template <typename T>
int ReduceRange(vector<T>& A) {
    vector<T> tmp = A;
    sort(tmp.begin(), tmp.end());
    tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
    unordered_map<T, int> uc;
    REP(i, 0, tmp.size()) {
        uc[tmp[i]] = i;
    }
    for (auto& v : A) {
        v = uc[v];
    }
    return tmp.size();
}
