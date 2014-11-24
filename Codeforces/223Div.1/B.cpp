#include <cstdio>
#include <algorithm>
#include <string.h>
#include <set>
using  namespace std;
const int N = 501000;
int n,m,tot,L[N],R[N],X[N],D[N];
int count(int x) {
        int ret = 0,p = 1;
        while (x>=p) {
                ret ++; p <<= 1;
        }
        return ret;
}
int get(int dep,int v,int p) {
        while (dep--) {
                v = v+count(v-1)+((v^(v&-v))==0 ? p : 0);
        }
        return v;
}
void addDot() {
        int t,l,r,x;
        scanf("%d%d%d%d",&t,&l,&r,&x);
        D[tot] = t;
        L[tot] = get(n-t,l,0);
        R[tot] = get(n-t,r,1);
        X[tot] = x;
        tot ++;
}
int query() {
        int t,v,l,r;
        scanf("%d%d",&t,&v);
        l = get(n-t,v,0);
        r = get(n-t,v,1);
        set<int> st;
        for (int i = 0; i < tot; i ++) if (D[i]>=t) {
                int ll = max(l,L[i]);
                int rr = min(r,R[i]);
                if (rr>=ll) st.insert(X[i]);
        }
        return (int)st.size();
}
int main() {
        scanf("%d%d",&n,&m);
        for (int i = 0; i < m; i ++) {
                int op;
                scanf("%d",&op);
                if (op==1) addDot();
                else printf("%d\n",query());
        }
        return 0;
}
