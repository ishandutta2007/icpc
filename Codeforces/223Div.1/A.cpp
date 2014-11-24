#include <stdio.h>
#include <algorithm>
using namespace std;
const int N = 201000;
int ar[N],tot;
int op[N],l[N],c[N],x[N],n,p;
long long cur;
int move(int l,int c) {
        while (tot<=100000 && c) {
                for (int i = 1; i <= l; i ++)
                        ar[++tot] = ar[i];
                c --;
        }
        return c;
}
int get(long long pos) {
        if (pos<=tot) return ar[pos];
        while (pos>cur && p<n) {
                if (op[p]==1) {
                        cur ++; p ++;
                        if (pos==cur) return x[p-1];
                } else {
                        long long tmp = (long long)l[p]*c[p];
                        if (tmp+cur<pos) {
                                cur += tmp;
                                p ++;
                        } else {
                                int xp = (pos-cur)%l[p];
                                if (xp==0) xp = l[p];
                                return ar[xp];
                        }
                }
        }
}
void work() {
        p = 0;
        for (int i = 0; i < n; i ++) {
                if (op[i]==1) {
                        ar[++tot] = x[i];
                } else {
                        c[i] = move(l[i],c[i]);
                        if (tot>100000) break;
                }
                p ++;
        }
        cur = tot;
        int nq;
        scanf("%d",&nq);
        while (nq--) {
                long long pos;
                scanf("%lld",&pos);
                printf("%d\n",get(pos));
        }
}
int main() {
        scanf("%d",&n);
        for (int i = 0; i < n; i ++) {
                scanf("%d",&op[i]);
                if (op[i]==1) {
                        scanf("%d",&x[i]);
                } else {
                        scanf("%d%d",&l[i],&c[i]);
                }
        }
        work();
        return 0;
}