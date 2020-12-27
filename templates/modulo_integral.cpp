template<int MOD>
struct Integral {
  int v_ = 0;

  Integral() {}
  Integral(int v) : Integral((long long)v) {}  // Implicit conversion is allowed.
  Integral(long long v) {
    if (v >= MOD) v -= MOD;
    if (v < 0) v += MOD;
    if (v >= MOD || v < 0) v = (v % MOD + MOD) % MOD;
    v_ = v;
  }
  ~Integral() = default;

  int val() const { return v_; }
  Integral operator + (const Integral& rhs) const { return Integral(val() + rhs.val()); }
  Integral operator - (const Integral& rhs) const { return Integral(val() - rhs.val()); }
  Integral operator * (const Integral& rhs) const { return Integral(val() * 1LL * rhs.val()); }
  Integral operator / (const Integral& rhs) const { return *this * rhs.inv(); }
  Integral operator - () const { return Integral(-val()); }
  Integral& operator += (const Integral& rhs) { *this = *this + rhs; return *this; }
  Integral& operator -= (const Integral& rhs) { *this = *this - rhs; return *this; }
  Integral& operator *= (const Integral& rhs) { *this = *this * rhs; return *this; }
  Integral& operator /= (const Integral& rhs) { *this = *this / rhs; return *this; }
  bool operator == (const Integral& rhs) { return val() == rhs.val(); }
  bool operator != (const Integral& rhs) { return !(*this == rhs); }

  Integral power(long long b) const {
    long long ret = 1 % MOD, a = v_;
    for ( ; b; b >>= 1, a = a * a % MOD) if (b & 1) ret = ret * a % MOD; return ret;
  }
  Integral inv() const { return power(MOD - 2); }
};
