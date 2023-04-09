// 维护N以内的素数表，解决素数相关的问题。
// 埃拉托斯特尼筛法，复杂度 O(NlglgN)
// 可以判定 N^2 范围以内的素数
// minPrime 记录每个数除自己外最小的质因数，可以用于稳定 $lgN$ 分解 N以内的数。
class PrimeList
{
public:
	unsigned int n;
	std::vector<unsigned int> primes;
    std::vector<unsigned int> minPrime;

	PrimeList(unsigned int n) {
		this->n = n;
		minPrime.resize(n + 1);
		unsigned int i;
		for (i = 2; i*i <= n; i++) {
			if (!minPrime[i]) {
				primes.push_back(i);
				for (int j = i * i; j <= n; j+=i) {
					if (!minPrime[j]) {
						minPrime[j] = i;
					}
				}
			}
		}
		for (;i <= n; i++) {
			if (!minPrime[i]) {
				primes.push_back(i);
			}
		}
	}

	bool isPrime(unsigned int v) {
		if (v == 1) { return false; }
		for (auto p : primes) {
			if (v <= p) return true;
			if (v % p == 0) return false;
		}
		return true;
	}

    bool isPrime(unsigned long long v) {
		if (v == 1) { return false; }
		for (auto p : primes) {
			if (v <= p) return true;
			if (v % p == 0) return false;
		}
		return true;
	}
};
