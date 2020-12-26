#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>

using LL = long long ;
const double pi = atan(1.) * 4;
const int kN = (1 << 18) + 5;

struct Complex {
  double x, y;
  Complex() {}
  Complex(double x, double y) : x(x), y(y) {}
  Complex operator + (const Complex &rhs) const { return Complex(x + rhs.x, y + rhs.y); }
  Complex operator - (const Complex &rhs) const { return Complex(x - rhs.x, y - rhs.y); }
  Complex operator * (const Complex &rhs) const { return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
  Complex conj() const { return Complex(x, -y); }
};

int L, rev[kN];
Complex omega[kN], omegaInv[kN];
void fft_init(int lim) {
  L = 1; while(L < lim) L<<=1;
  for(int i=0; i<L; i++) {
    omega[i] = Complex(cos(2*pi/L*i), sin(2*pi/L*i));
    omegaInv[i] = omega[i].conj();
  }
}
void fft(Complex *a, int n, int flag) {
  Complex *w = flag == 1 ? omega : omegaInv;
  int k = 0; while((1<<k) < n) k++;
  for(int i=0; i<n; i++) {
    rev[i] = (rev[i>>1]>>1) | ((i&1)<<(k-1));
    if(i < rev[i]) std::swap(a[i], a[rev[i]]);
  }
  for(int l=2; l<=n; l<<=1) {
    int m = l>>1;
    for(Complex *p = a; p != a+n; p += l) 
      for(int k=0; k<m; k++) {
        Complex t = w[L/l*k] * p[k+m];
        p[k+m] = p[k] - t;
        p[k] = p[k] + t;
      }
  }
  if(flag == -1) for(int i=0; i<n; i++) a[i].x /= n;
}

void mul(int *x, int lx, int *y, int ly, int *z)
{
  fft_init(lx + ly);
  static Complex p[kN << 2], q[kN << 2];
  for (int i = 0; i < L; ++ i)
    p[i] = q[i] = Complex(0., 0.);
  for (int i = 0; i < lx; ++ i)
    p[i] = Complex(x[i], 0.);
  for (int i = 0; i < ly; ++ i)
    q[i] = Complex(y[i], 0.);
  fft(p, L, 1); fft(q, L, 1);
  for (int i = 0; i < L; ++ i)
    p[i] = p[i] * q[i];
  fft(p, L, -1);
  for (int i = 0; i < lx + ly - 1; ++ i)
    z[i] = int(p[i].x + .5);
}

void example()
{
  int a[3] = {1, 2, 3}, b[4] = {1, 2, 3, 4};
  int c[6];
  mul(a, 3, b, 4, c);
  for (int i = 0; i < 6; ++ i)
    printf("%d%c", c[i], " \n"[i + 1 == 6]);
  // 1 4 10 16 17 12
}

int main()
{
  example();
}
