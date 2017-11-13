#include <stdio.h>
#include <math.h>
#include <algorithm>

using LL = long long;
const int MOD = 1e6 + 3;
const int kN = (1 << 18) + 5;

const double PI = atan(1.) * 4;

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
        omega[i] = Complex(cos(2*PI/L*i), sin(2*PI/L*i));
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

void mul_any(const int *x, int lx, const int *y, int ly, int *z)
{
    static Complex a[kN << 1], b[kN << 1], c[kN << 1], d[kN << 1];
    for (int i = 0; i < lx; ++ i)
        a[i] = Complex(x[i] >> 15, 0.), b[i] = Complex(x[i] & 32767, 0.);
    for (int i = lx; i < L; ++ i)
        a[i] = b[i] = Complex(0., 0.);
    for (int i = 0; i < ly; ++ i)
        c[i] = Complex(y[i] >> 15, 0.), d[i] = Complex(y[i] & 32767, 0.);
    for (int i = ly; i < L; ++ i)
        c[i] = d[i] = Complex(0., 0.);
    fft(a, L, 1); fft(b, L, 1); fft(c, L, 1); fft(d, L, 1);
    for (int i = 0; i < L; ++ i) {
        Complex ta = a[i], tb = b[i], tc = c[i], td = d[i];
        a[i] = ta * tc;
        b[i] = ta * td + tb * tc;
        c[i] = tb * td;
    }
    fft(a, L, -1); fft(b, L, -1); fft(c, L, -1);
    for (int i = 0; i < L; ++ i)
        z[i] = ((LL(a[i].x + .5) % MOD << 30) +
                (LL(b[i].x + .5) % MOD << 15) +
                LL(c[i].x + .5) % MOD) % MOD;
}

int main()
{
    scanf("%d", &n);
    fft_init(n + n + 1);
}
