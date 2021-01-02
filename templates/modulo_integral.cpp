template<int MOD>
struct Integral {
  int v_ = 0;

  template<typename T> Integral(T v) : v_(norm(v)) {  // Implicit conversion is allowed.
    static_assert(std::is_integral<T>::value, "input should be an integral.");
  }
  Integral() = default;
  ~Integral() = default;

  template<typename T> T norm(T v) const {
    if (v >= MOD) v -= MOD;
    if (v < 0) v += MOD;
    if (v >= MOD || v < 0) v = (v % MOD + MOD) % MOD;
    return v;
  }

  int val() const { return v_; }
  Integral operator + (const Integral& rhs) const { return Integral(val() + rhs.val()); }
  Integral operator - (const Integral& rhs) const { return Integral(val() - rhs.val()); }
  Integral operator * (const Integral& rhs) const { return Integral(val() * 1LL * rhs.val()); }
  Integral operator / (const Integral& rhs) const { return *this * rhs.inv(); }
  Integral& operator += (const Integral& rhs) { return *this = *this + rhs; }
  Integral& operator -= (const Integral& rhs) { return *this = *this - rhs; }
  Integral& operator *= (const Integral& rhs) { return *this = *this * rhs; }
  Integral& operator /= (const Integral& rhs) { return *this = *this / rhs; }
  bool operator == (const Integral& rhs) const { return val() == rhs.val(); }
  bool operator != (const Integral& rhs) const { return !(*this == rhs); }
  const Integral operator - () const { return Integral(-val()); }
  const Integral operator ++ () { v_ = norm(v_ + 1); return *this; }
  const Integral operator ++ (int) { Integral ret = *this; ++(*this); return ret; }
  const Integral operator -- () { v_ = norm(v_ - 1); return *this; }
  const Integral operator -- (int) { Integral ret = *this; --(*this); return ret; }

  Integral power(long long b) const {
    long long ret = 1 % MOD, a = v_;
    for ( ; b; b >>= 1, a = a * a % MOD) if (b & 1) ret = ret * a % MOD; return ret;
  }
  Integral inv() const { return power(MOD - 2); }
};

template<int MOD>
std::string to_string(const Integral<MOD>& v) {
  return std::string("Integral{v=") + std::to_string(v.val()) + "}";
}

template<int MOD, bool kByDefinition = false>
struct Binomial {
  std::vector<Integral<MOD>> factor, inv_factor;

  explicit Binomial(int n = 0) : factor(n + 1), inv_factor(n + 1) {
    factor[0] = 1;
    for (int i = 1; i <= n; ++i) factor[i] = factor[i - 1] * i;
    inv_factor[n] = factor[n].inv();
    for (int i = n; i >= 1; --i) inv_factor[i - 1] = inv_factor[i] * i;
  }
  ~Binomial() = default;

  template<typename T>
  Integral<MOD> operator () (T a, T b) const {
    if (a < b || b < 0) return 0;
    if (a < factor.size()) return factor[a] * inv_factor[b] * inv_factor[a - b];
    if constexpr(!kByDefinition) {
      throw std::out_of_range("Accessing Binomial Out of Range.");
    } else {
      b = std::min(b, a - b);
      Integral<MOD> ret = 1;
      for (T i = 1; i <= b; ++i) ret = ret * (a + 1 - i) / i;
      return ret;
    }
  }
};

const int MOD = 998244353;
using Mint = Integral<MOD>;
using Binom = Binomial<MOD>;

// Binom binom(200000);

