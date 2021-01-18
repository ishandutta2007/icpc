std::vector<int> primes;
std::vector<int> mu;
std::vector<int> min_div;

void prepare_primes(int n) {
	min_div.resize(n + 1);
	mu.resize(n + 1);
	min_div[1] = mu[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!min_div[i]) {
			primes.emplace_back(i);
			min_div[i] = i;
			mu[i] = -1;
		}
		for (int p : primes) {
			if (i * p > n) break;
			min_div[i * p] = p;
			if (i % p == 0) break;
			else mu[i * p] = -mu[i];
		}
	}
}
