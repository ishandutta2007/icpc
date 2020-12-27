double F(double x) {
  // 待积分函数
  return sqrt(1 + 4 * a * a * x * x);
}
double simpson(double a,double b) {
  double c = (a + b) * .5;
  return (F(a) + 4 * F(c) + F(b)) * (b - a) / 6;
}
double asr(double a,double b,double eps,double A) {
  double c = (a + b) * .5;
  double L = simpson(a,c),R = simpson(c,b);
  if (std::abs(L + R - A) <= 15 * eps) {
    return L + R + (L + R - A) / 15;
  }
  return asr(a,c,eps / 2,L) + asr(c,b,eps / 2,R);
}
double calc(double L,double R) {
  return asr(L,R,1e-5,simpson(L,R));
}
