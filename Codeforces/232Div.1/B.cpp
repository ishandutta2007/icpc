#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int N = 101000;
typedef long long lld;
int prm[N],ptot;
void init() {
        for (int i = 2; i < N; i ++) if (!prm[i]) {
                prm[ptot++] = i;
                for (int j = i+i; j < N; j += i) prm[j] = 1;
        }
}
bool isprim(int x) {
        for (int i = 0; i < ptot && prm[i]*prm[i]<=x; i ++) {
                if (x%prm[i]==0) return false;
        }
        return true;
}
lld gcd(lld a,lld b) {
        return b==0 ? a : gcd(b,a%b);
}
void work(int n) {
        lld a,b;
        lld i,j,fuck = 1;
        for (i = n; !isprim(i); i --) fuck ++;
        for (j = n+1; !isprim(j); j ++);
        a = i*j-2*j+2*fuck;
        b = 2*i*j;
        lld vg = gcd(a,b);
        a /= vg;
        b /= vg;
        printf("%lld/%lld\n",a,b);
}
int main() {
        int cas,n;
        init();
        scanf("%d",&cas);
        while (cas--) {
                scanf("%d",&n);
                work(n);
        }
        return 0;
}