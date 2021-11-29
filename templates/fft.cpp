#include <bits/stdc++.h>

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

struct FastFourierTransform {
 public:
  static void multiply(int* x, int lx, int* y, int ly, int* z) {
    FastFourierTransform fft(lx + ly);
    int L = fft.L;
    std::vector<Complex> p(L), q(L);
    for (int i = 0; i < lx; ++ i) p[i].x = x[i];
    for (int i = 0; i < ly; ++ i) q[i].x = y[i];
    fft.fft(&p[0], L, 1);
    fft.fft(&q[0], L, 1);
    for (int i = 0; i < L; ++ i) p[i] = p[i] * q[i];
    fft.fft(&p[0], L, -1);
    for (int i = 0; i < lx + ly - 1; ++ i) z[i] = int(p[i].x + .5);
  }

  explicit FastFourierTransform(int lim = 1) {
    init(lim);
  }

  void init(int lim) {
    L = 1; while(L < lim) L <<= 1;
    omega.resize(L);
    omega_inv.resize(L);
    for(int i = 0; i < L; ++i) {
      omega[i] = Complex(std::cos(2 * PI / L * i), std::sin(2 * PI / L * i));
      omega_inv[i] = omega[i].conj();
    }
  }

  void fft(Complex* a, int n, int flag) {
    // flag == 1 : forward; flag == -1 : inverse.
    assert(n == L);
    const std::vector<Complex>& w = flag == 1 ? omega : omega_inv;
    int k = 0; while((1 << k) < n) ++k;
    std::vector<int> rev(n);
    for(int i = 0; i < n; ++i) {
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
      if(i < rev[i]) std::swap(a[i], a[rev[i]]);
    }
    for(int l = 2; l <= n; l <<= 1) {
      int m = l >> 1;
      for(Complex* p = a; p != a + n; p += l)
        for(int k = 0; k < m; ++k) {
          Complex t = w[L / l * k] * p[k + m];
          p[k + m] = p[k] - t;
          p[k] = p[k] + t;
        }
    }
    if(flag == -1) for(int i = 0; i < n; ++i) a[i].x /= n;
  }

 private:
  static constexpr double PI = std::atan2(0.0, -1.0);

  int L = 1;
  std::vector<Complex> omega, omega_inv;
};

void example() {
  int a[3] = {1, 2, 3}, b[4] = {1, 2, 3, 4};
  int c[6];
  FastFourierTransform::multiply(a, 3, b, 4, c);
  for (int i = 0; i < 6; ++ i)
    printf("%d%c", c[i], " \n"[i + 1 == 6]);
  // 1 4 10 16 17 12
}

int main() {
  example();
}
