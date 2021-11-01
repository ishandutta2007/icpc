struct PrimeTable {
  std::vector<int> primes;
  std::vector<int> min_div;
  std::vector<int8_t> mu;

  PrimeTable() = default;
  explicit PrimeTable(int n) { prepare_primes(n); }

  void prepare_primes(int n) {
    primes.clear();
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

  bool is_prime(long long x) const {
    if (x < 2) return false;
    if (x < min_div.size()) return min_div[x] == x;
    for (long long w = 2; w * w <= x; ++w) if (x % w == 0) return false;
    return true;
  }
};

