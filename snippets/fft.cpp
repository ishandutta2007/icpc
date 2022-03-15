struct Complex {
  double x = 0.0;
  double y = 0.0;

  Complex() {}
  Complex(double x, double y) : x(x), y(y) {}
  Complex operator + (const Complex &rhs) const { return Complex(x + rhs.x, y + rhs.y); }
  Complex operator - (const Complex &rhs) const { return Complex(x - rhs.x, y - rhs.y); }
  Complex operator * (const Complex &rhs) const { return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
  Complex conj() const { return Complex(x, -y); }
};

template<typename T>
struct Polynomial final : public std::vector<T> {
  Polynomial() = default;
  explicit Polynomial(int n) : std::vector<T>(n) {}
  Polynomial(int n, const T& val) : std::vector<T>(n, val) {}
  Polynomial(std::initializer_list<T> initializer_list) : std::vector<T>(std::move(initializer_list)) {}
  Polynomial(std::vector<T> vec) : std::vector<T>(std::move(vec)) {}
  int size() const { return std::vector<T>::size(); }
  T get(int pos) const { return pos >= 0 && pos < size() ? (*this)[pos] : T(0); }
  T& touch(int pos) { if (pos >= size()) std::vector<T>::resize(pos + 1, T(0)); return (*this)[pos]; }
  Polynomial mod(int n) const { return Polynomial(std::vector<T>(this->data(), this->data() + std::min(n, size()))); }
};

struct FastFourierTransform {
 public:
  template<typename T>
  static Polynomial<T> multiply(const Polynomial<T>& x, const Polynomial<T>& y) {
    const int L = binary_upper_bound((int)x.size() - 1 + (int)y.size() - 1);
    if constexpr(std::is_same<T, Complex>::value) {
      Polynomial<Complex> p = x, q = y;
      fft(p, L, 1);
      fft(q, L, 1);
      for (int i = 0; i < L; ++ i) p[i] = p[i] * q[i];
      fft(p, L, -1);
      return p;
    } else {
      Polynomial<Complex> p(L), q(L);
      for (int i = 0; i < x.size(); ++ i) p[i].x = x[i];
      for (int i = 0; i < y.size(); ++ i) q[i].x = y[i];
      fft(p, L, 1);
      fft(q, L, 1);
      for (int i = 0; i < L; ++ i) p[i] = p[i] * q[i];
      fft(p, L, -1);
      Polynomial<T> z(std::max(0, (int)x.size() + (int)y.size() - 1));
      for (int i = 0; i < z.size(); ++i) {
        z[i] = std::is_integral<T>::value ? p[i].x + 0.5 : p[i].x;
      }
      return z;
    }
  }

  static Polynomial<int> multiply_mod_any(const Polynomial<int>& x, const Polynomial<int>& y, int mod) {
    const int L = binary_upper_bound((int)x.size() - 1 + (int)y.size() - 1);
    Polynomial<Complex> a(L), b(L), c(L), d(L);
    for (int i = 0; i < x.size(); ++i) {
      a[i].x = x[i] >> 15;
      b[i].x = x[i] & 32767;
    }
    for (int i = 0; i < y.size(); ++i) {
      c[i].x = y[i] >> 15;
      d[i].x = y[i] & 32767;
    }
    fft(a, L, 1);
    fft(b, L, 1);
    fft(c, L, 1);
    fft(d, L, 1);
    for (int i = 0; i < L; ++i) {
      Complex ta = a[i], tb = b[i], tc = c[i], td = d[i];
      a[i] = ta * tc;
      b[i] = ta * td + tb * tc;
      c[i] = tb * td;
    }
    fft(a, L, -1);
    fft(b, L, -1);
    fft(c, L, -1);
    Polynomial<int> z(std::max(0, (int)x.size() + (int)y.size() - 1));
    for (int i = 0; i < z.size(); ++ i) {
      z[i] = (((long long)(a[i].x + .5) % mod << 30) +
              ((long long)(b[i].x + .5) % mod << 15) +
              (long long)(c[i].x + .5) % mod) % mod;
    }
    return z;
  }

  static void fft(Complex a[], int L, int flag) {
    // flag == 1 : forward; flag == -1 : inverse.
    // L should be a power of 2.
    int k = binary_upper_bound_in_bits(L - 1);
    assert(1 << k == L);
    prepare_bits(k);
    const std::vector<Complex>& w = flag == 1 ? omega[k] : omega_inv[k];
    std::vector<int> rev(L);
    for(int i = 0; i < L; ++i) {
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
      if(i < rev[i]) std::swap(a[i], a[rev[i]]);
    }
    for(int l = 2; l <= L; l <<= 1) {
      int m = l >> 1;
      for(Complex* p = a; p != a + L; p += l)
        for(int k = 0; k < m; ++k) {
          Complex t = w[L / l * k] * p[k + m];
          p[k + m] = p[k] - t;
          p[k] = p[k] + t;
        }
    }
    if(flag == -1) for(int i = 0; i < L; ++i) a[i].x /= L;
  }
  static void fft(Polynomial<Complex>& poly, int n, int flag) {
    if (poly.size() < n) poly.resize(n, Complex{});
    return fft(&poly[0], n, flag);
  }

 private:
  static constexpr double PI = 3.14159265358979323846;

  static int binary_upper_bound_in_bits(int w) {
    if (w <= 0) return 1;
    const int highbit = 31 - __builtin_clz(w);
    return highbit + 1;
  }
  static int binary_upper_bound(int w) { return 1 << binary_upper_bound_in_bits(w); }

  static void prepare_bits(int num_bits) {
    if (num_bits >= omega.size()) {
      omega.resize(std::max(num_bits + 1, 21));
      omega_inv.resize(std::max(num_bits + 1, 21));
    }
    if (omega[num_bits].empty()) {
      int L = 1 << num_bits;
      omega[num_bits].resize(L);
      omega_inv[num_bits].resize(L);
      for(int i = 0; i < L; ++i) {
        omega[num_bits][i] = Complex(std::cos(2 * PI / L * i), std::sin(2 * PI / L * i));
        omega_inv[num_bits][i] = omega[num_bits][i].conj();
      }
    }
  }

  static std::vector<std::vector<Complex>> omega;
  static std::vector<std::vector<Complex>> omega_inv;
};

std::vector<std::vector<Complex>> FastFourierTransform::omega;
std::vector<std::vector<Complex>> FastFourierTransform::omega_inv;

void example() {
  Polynomial<int> a{1, 2, 3}, b{1, 2, 3, 4};
  Polynomial<int> c = FastFourierTransform::multiply(a, b);
  DUMP(c);  // 1 4 10 16 17 12
  DUMP(FastFourierTransform::multiply_mod_any(a, b, 5));  // 1 4 0 1 2 2

  Polynomial<double> d{1.1, 2.1, 3.1}, e{1.1, 2.1, 3.1, 4.1};
  Polynomial<double> f = FastFourierTransform::multiply(d, e);
  DUMP(f);
}

