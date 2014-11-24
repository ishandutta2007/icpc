#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <cstring>
using namespace std;
const int N = 101000;
int n,K,head[N],etot,dfn[N],dfp[N],plca[N][20],dep[N],tim,sum;
struct edge { int v,next; } g[N<<1];
set<int> st;
void add_edge(int u,int v) {
        g[etot] = (edge) {v,head[u]};
        head[u] = etot ++;
}
void dfs(int u,int fa,int deep) {
        dep[u] = deep;
        plca[u][0] = fa;
        dfn[u] = ++tim;
        dfp[tim] = u;
        for (int i = 1; i < 20; i ++)
                if (plca[u][i-1]!=-1)
                        plca[u][i] = plca[plca[u][i-1]][i-1];
        for (int i = head[u]; i != -1; i = g[i].next) {
                int v = g[i].v;
                if (v==fa) continue;
                dfs(v,u,deep+1);
        }
}
int lca(int a,int b) {
        if (dep[a]<dep[b]) swap(a,b);
        int delta = dep[a]-dep[b];
        for (int i = 19; i >= 0; i --)
                if (delta>>i&1) a = plca[a][i];
        if (a!=b) {
                for (int i = 19; i >= 0; i --)
                        if (plca[a][i]!=plca[b][i]) a = plca[a][i], b = plca[b][i];
                a = plca[a][0];
        }
        return a;
}
int dis(int a,int b) {
        return dep[a]+dep[b]-dep[lca(a,b)]*2;
}
int calc(int u) {
        st.insert(dfn[u]);
        int prev,next;
        set<int>::iterator it;
        it = st.find(dfn[u]);
        prev = dfp[*(it!=st.begin() ? --it : --st.end())];
        it = st.find(dfn[u]);
        next = dfp[*(it!=--st.end() ? ++it : st.begin())];
        st.erase(dfn[u]);
        return dis(u,prev)+dis(u,next)-dis(prev,next);
}
int main() {
        cin >> n >> K;
        memset(head,-1,sizeof(head));
        memset(plca,-1,sizeof(plca));
        for (int i = 0; i < n-1; i ++) {
                int a,b;
                cin >> a >> b;
                add_edge(a,b);
                add_edge(b,a);
        }
        dfs(1,-1,0);
        int ans = 0,j = 1,d;
        for (int i = 1; i <= n; i ++) {
                while (j<=n && ((d=calc(j))+sum)/2+1<=K) sum += d,st.insert(dfn[j++]);
                ans = max(ans,j-i);
                sum -= calc(i);
        }
        cout << ans << endl;
        return 0;
}
