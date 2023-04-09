// 线性复杂度素数表，但实际跑的没有非线性的快
class PrimeList
{
	int n;
	std::vector<int> primes;
	std::vector<int> minPrime;
public:
	PrimeList(int n) {
		this->n = n;
		minPrime.resize(n + 1);
		int i;
		for (i = 2; i*i <= n; i++) {
			if (!minPrime[i]) {
				primes.push_back(i);
			}
			int up = n / i;
			for (auto v : primes) {
				if (v > up) break;
				minPrime[i * v] = v;
				if (i % v == 0) break;
			}
		}
		for (; i <= n; i++) {
			if (!minPrime[i]) {
				primes.push_back(i);
			}
		}
	}
};
