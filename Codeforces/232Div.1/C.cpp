#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lld;
const int MOD = 1e9+7,N = 301000;
vector<int> edge[N];
int n,st[N],ed[N],dep[N],tim,C[N],B[N];
void dfs(int u,int deep) {
        dep[u] = deep;
        st[u] = tim ++;
        for (int i = 0; i < (int)edge[u].size(); i ++) {
                int v = edge[u][i];
                dfs(v,deep+1);
        }
        ed[u] = tim-1;
}
void add(int &a,int b) { a += b; a %= MOD; }
void modify(int *C,int p,int dt) {
        for (int i = p; i < N; i += i&-i) add(C[i],dt);
}
int query(int *C,int p) {
        int ret = 0;
        for (int i = p; i > 0; i -= i&-i) add(ret,C[i]);
        return ret;
}
int main() {
        scanf("%d",&n);
        for (int i = 1; i < n; i ++) {
                int x;
                scanf("%d",&x); x --;
                edge[x].push_back(i);
        }
        tim = 1;
        dfs(0,0);
        int nq;
        scanf("%d",&nq);
        while (nq--) {
                int op,v,x,k;
                scanf("%d",&op);
                if (op==1) {
                        scanf("%d%d%d",&v,&x,&k); v --;
                        modify(B,st[v],((lld)dep[v]*k%MOD+x)%MOD);
                        modify(B,ed[v]+1,-(((lld)dep[v]*k%MOD+x)%MOD));
                        modify(C,st[v],k);
                        modify(C,ed[v]+1,-k);
                } else {
                        scanf("%d",&v); v --;
                        int val = query(B,st[v]);
                        int slo = query(C,st[v]);
                        int ans = ((val-(lld)slo*dep[v]%MOD)%MOD+MOD)%MOD;
                        printf("%d\n",ans);
                }
        }
        return 0;
}