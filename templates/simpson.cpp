struct Simpson {
 public:
  // f is the function to be integrated.
  // F :: double -> double
  // e.g. double f(double x) { return std::sqrt(1 + 4 * a * a * x * x); }
  template<typename F>
  static double calc(double L, double R, F&& f) {
    return asr(L, R, 1e-5, simpson(L, R, std::forward<F>(f)), std::forward<F>(f));
  }

 private:
  template<typename F>
  static double simpson(double a, double b, F&& f) {
    double c = (a + b) * .5;
    return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6;
  }
  template<typename F>
  static double asr(double a, double b, double eps, double A, F&& f) {
    double c = (a + b) * .5;
    double L = simpson(a, c, std::forward<F>(f)), R = simpson(c, b, std::forward<F>(f));
    if (std::abs(L + R - A) <= 15 * eps) {
      return L + R + (L + R - A) / 15;
    }
    return asr(a, c, eps / 2, L, std::forward<F>(f)) + asr(c, b, eps / 2, R, std::forward<F>(f));
  }
};

