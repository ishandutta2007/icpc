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

  template<typename T>
  std::vector<T> get_factors_with_nonzero_mu(T x) const {  // Note: Not in ascending order.
    assert(x >= 1);
    const std::vector<typename std::pair<T, T>> repr = get_canonical_representation(x);
    std::vector<T> factors;
    std::function<void(int, T)> enumerate_factors = [&](int at, T val) -> void {
      factors.emplace_back(val);
      for (int i = at; i < repr.size(); ++i) {
        enumerate_factors(i + 1, val * repr[i].first);
      }
    };
    enumerate_factors(0, 1);
    return factors;
  }

  template<typename T, typename Vector = std::vector<T>>
  T get_pi(T n, Vector&& entries, Vector&& g) const {
    // pi(n) = \sum_{i=2}^{n}[is_prime(i)].
    // min_25 sieve.
    // O(n^{3/4}/log(n)).
    assert(!primes.empty());
    assert(primes.back() * 1LL * primes.back() >= n);
    entries.clear();
    g.clear();

    for (T i = 1; i <= n; i = n / (n / i) + 1) entries.emplace_back(n / i);
    std::reverse(entries.begin(), entries.end());
    int m = entries.size();
    g.resize(m, 0);
    for (int i = 0; i < m; ++i) g[i] = entries[i] - 1;

    int w = std::sqrt(n);
    while ((w + 1) * 1LL * (w + 1) <= n) ++w;
    std::vector<T> small(w + 1), big(w + 1);
    for (int i = 1, j = 0; i <= w; ++i) {
      while (j < m && entries[j] < i) ++j;
      assert(entries[j] == i);
      small[i] = j;
    }
    for (int i = w, j = 0; i >= 1; --i) {
      while (j < m && entries[j] < n / i) ++j;
      assert(entries[j] == n / i);
      big[i] = j;
    }
    auto get_index = [&](T x) -> int {
      return x <= w ? small[x] : big[n / x];
    };

    for (int k = 0; k < primes.size(); ++k) {
      int p = primes[k];
      if (p * 1LL * p > n) break;
      for (int i = m - 1; i >= 0 && entries[i] >= p * 1LL * p; --i) {
        g[i] += -g[get_index(entries[i] / p)] + k;
      }
    }
    return g.back();
  }
  template<typename T>
  T get_pi(T n) const { return get_pi(n, std::vector<T>{}, std::vector<T>{}); }
};

