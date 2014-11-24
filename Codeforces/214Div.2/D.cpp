/* Created Time: Monday, November 25, 2013 AM08:43:43 CST */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1111;
const int M = 3333;
int n,m;
struct edge {
    int v,l,r,next;
}g[M<<1];
int head[N],etot;
void add_edge(int u,int v,int l,int r) {
    g[etot].v = v; g[etot].l = l; g[etot].r = r;
    g[etot].next = head[u]; head[u] = etot ++;
};
int a[M],b[M],vis[N],tim;
bool dfs(int u,int l,int r) {
    if (vis[u]==tim) return false;
    vis[u] = tim;
    if (u==n) return true;
    for (int i = head[u]; i != -1; i = g[i].next) {
        edge &e = g[i];
        if (e.l>l || e.r<r) continue;
        if (dfs(e.v,l,r)) return true;
    }
    return false;
}
void work() {
    sort(a,a+m);
    sort(b,b+m);
    int ans = 0;
    for (int i = 0; i < m; i ++) {
        int l = 0,r = m-1;
        while (l<=r) {
            int mid = l+r>>1;
            tim ++;
            if (dfs(1,a[i],b[mid])) {
                ans = max(ans,b[mid]-a[i]+1);
                l = mid+1;
            } else r = mid-1;
        }
    }
    if (ans==0) puts("Nice work, Dima!");
    else printf("%d\n",ans);
}
int main() {
    scanf("%d%d",&n,&m);
    memset(head,-1,sizeof(head));
    etot = 0;
    for (int i = 0; i < m; i ++) {
        int u,v,l,r;
        scanf("%d%d%d%d",&u,&v,&l,&r);
        add_edge(u,v,l,r);
        add_edge(v,u,l,r);
        a[i] = l;
        b[i] = r;
    }
    work();
    return 0;
}
