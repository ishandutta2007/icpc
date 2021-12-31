struct PrimeTable {
  std::vector<int> primes;
  std::vector<int> min_div;
  std::vector<int8_t> mu;
  std::vector<int> phi;

  PrimeTable() = default;
  explicit PrimeTable(int n) { prepare_primes(n); }

  void prepare_primes(int n) {
    primes.clear();
    min_div.assign(n + 1, 0);
    mu.assign(n + 1, 0);
    phi.assign(n + 1, 0);
    min_div[1] = mu[1] = phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!min_div[i]) {
        primes.emplace_back(i);
        min_div[i] = i;
        mu[i] = -1;
        phi[i] = i - 1;
      }
      for (int p : primes) {
        if (i * p > n) break;
        min_div[i * p] = p;
        if (i % p == 0) {
          phi[i * p] = phi[i] * p;
          break;
        } else {
          mu[i * p] = -mu[i];
          phi[i * p] = phi[i] * (p - 1);
        }
      }
    }
  }

  template<typename T>
  bool is_prime(T x) const {
    if (x < 2) return false;
    if (x < min_div.size()) return min_div[x] == x;
    for (T w = 2; w * w <= x; ++w) if (x % w == 0) return false;
    return true;
  }

  template<typename T>
  std::vector<typename std::pair<T, T>> get_canonical_representation(T x) const {
    assert(x >= 1);
    std::vector<typename std::pair<T, T>> ret;  // <prime, cnt>
    for (T i = 2; x >= min_div.size() && i * i <= x; ++i) if (x % i == 0) {
      T cnt = 0;
      while (x % i == 0) ++cnt, x /= i;
      ret.emplace_back(i, cnt);
    }
    while (1 < x && x < min_div.size()) {
      T p = min_div[x];
      T cnt = 0;
      while (x % p == 0) ++cnt, x /= p;
      ret.emplace_back(p, cnt);
    }
    if (x >= min_div.size() && x > 1) {
      ret.emplace_back(x, 1);
    }
    return ret;
  }

  template<typename T>
  std::vector<T> get_factors(T x) const {  // Note: Not in ascending order.
    assert(x >= 1);
    const std::vector<typename std::pair<T, T>> repr = get_canonical_representation(x);
    std::vector<T> factors;
    std::function<void(int, T)> enumerate_factors = [&](int at, T val) -> void {
      factors.emplace_back(val);
      for (int i = at; i < repr.size(); ++i) {
        T tmp = val;
        for (int j = 0; j < repr[i].second; ++j) {
          tmp *= repr[i].first;
          enumerate_factors(i + 1, tmp);
        }
      }
    };
    enumerate_factors(0, 1);
    return factors;
  }
};

