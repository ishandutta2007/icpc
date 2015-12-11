// matroid intersection algorithm 求两棵边不相交的生成树
#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int N = 110;
const int M = 333<<1;

int head[N],etot,n,m,e[2][M],last[M],ch[M],prev[N],preu[N];
struct edge {int v,next;} g[M];
bool mark[N],vis[M];

void add_edge(int u,int v) {
    g[etot].v = v; g[etot].next = head[u]; head[u] = etot ++;
}

bool find_cycle(int flag,int x,int p) {
    if (x==p) return true;
    for (int i = head[x]; i != -1; i = g[i].next) {
        int v = g[i].v;
        if (ch[i>>1]==flag && !mark[v]) {
            mark[v] = true;
            prev[v] = i>>1<<1|flag;
            preu[v] = x;
            if (find_cycle(flag,v,p)) 
                return true;
        }
    }
    return false;
}

bool bfs(int ip) {
    int qf,qe,q = 0;
    int que[M];
    bool inq[M] = {0};
    que[q++] = ip<<1;
    que[q++] = ip<<1|1;
    inq[ip<<1] = true;
    inq[ip<<1|1] = true;
    qf = 0;
    qe = q;
    while (qf!=qe) {
        while (qf!=qe) {
            int c = que[qf++];
            memset(mark,0,sizeof(mark));
            mark[e[0][c>>1]] = true;
            if (!find_cycle(c&1,e[0][c>>1],e[1][c>>1])) {
                while ((c>>1)!=ip) {
                    ch[c>>1] ^= 1;
                    c = last[c];
                }
                ch[ip] = c&1;
                return true;
            }
            for (int i = e[1][c>>1]; i != e[0][c>>1]; i = preu[i]) {
                int j = prev[i]^1;
                if (!inq[j]) {
                    inq[j] = true;
                    que[q++] = j;
                    last[j] = c;
                }
            }
        }
        qe = q;
    }
    return false;
}

int main() {
    int cas,ca = 0;
    scanf("%d",&cas);
    while (cas--) {
        scanf("%d%d",&n,&m);
        memset(head,-1,sizeof(head)); etot = 0;
        memset(ch,-1,sizeof(ch));
        int cnt = 0;
        for (int i = 0; i < m; ++ i) {
            int a,b;
            scanf("%d%d",&a,&b);
            e[0][i] = a;
            e[1][i] = b;
            add_edge(a,b);
            add_edge(b,a);
            cnt += bfs(i);
        }
        printf("Case %d: ",++ca);
        puts(cnt==(n-1<<1) ? "YES" : "NO");
    }
    return 0;
}
